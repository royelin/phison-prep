// SPDX-License-Identifier: GPL-2.0
/*
 * dummy_driver.c - Minimal Linux character device driver (study skeleton)
 *
 * Demonstrates: module init/exit, cdev registration, file_operations,
 * an internal ring buffer for read/write, and a module parameter.
 *
 * Build:  make
 * Load:   sudo insmod dummy_driver.ko
 * Test:   echo "hello" > /dev/dummy0
 *         cat /dev/dummy0
 * Remove: sudo rmmod dummy_driver
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/slab.h>

#define DRIVER_NAME     "dummy"
#define CLASS_NAME      "dummy_class"
#define BUF_SIZE        4096

static int num_devices = 1;
module_param(num_devices, int, 0444);
MODULE_PARM_DESC(num_devices, "Number of dummy devices to create (default: 1)");

struct dummy_dev {
	struct cdev  cdev;
	struct mutex lock;
	char         *buf;
	size_t        head;   /* write position */
	size_t        tail;   /* read position  */
	size_t        count;  /* bytes currently in buffer */
};

static dev_t           dev_base;
static struct class   *dummy_class;
static struct dummy_dev *devices;

/* ------------------------------------------------------------------ */

static int dummy_open(struct inode *inode, struct file *filp)
{
	struct dummy_dev *dev = container_of(inode->i_cdev,
					     struct dummy_dev, cdev);
	filp->private_data = dev;
	pr_info("%s: opened minor %u\n", DRIVER_NAME, iminor(inode));
	return 0;
}

static int dummy_release(struct inode *inode, struct file *filp)
{
	pr_info("%s: closed minor %u\n", DRIVER_NAME, iminor(inode));
	return 0;
}

static ssize_t dummy_read(struct file *filp, char __user *ubuf,
			   size_t count, loff_t *ppos)
{
	struct dummy_dev *dev = filp->private_data;
	ssize_t ret = 0;

	if (mutex_lock_interruptible(&dev->lock))
		return -ERESTARTSYS;

	/* Block until data is available when O_NONBLOCK is not set */
	if (dev->count == 0) {
		mutex_unlock(&dev->lock);
		return 0;   /* EOF */
	}

	count = min(count, dev->count);

	/*
	 * The ring buffer may wrap around; copy in at most two pieces:
	 * from tail to end-of-buffer, then from start-of-buffer.
	 */
	if (dev->tail + count <= BUF_SIZE) {
		if (copy_to_user(ubuf, dev->buf + dev->tail, count)) {
			ret = -EFAULT;
			goto out;
		}
	} else {
		size_t first  = BUF_SIZE - dev->tail;
		size_t second = count - first;

		if (copy_to_user(ubuf, dev->buf + dev->tail, first) ||
		    copy_to_user(ubuf + first, dev->buf, second)) {
			ret = -EFAULT;
			goto out;
		}
	}

	dev->tail   = (dev->tail + count) % BUF_SIZE;
	dev->count -= count;
	ret         = count;

out:
	mutex_unlock(&dev->lock);
	return ret;
}

static ssize_t dummy_write(struct file *filp, const char __user *ubuf,
			    size_t count, loff_t *ppos)
{
	struct dummy_dev *dev = filp->private_data;
	ssize_t ret = 0;
	size_t  avail;

	if (mutex_lock_interruptible(&dev->lock))
		return -ERESTARTSYS;

	avail = BUF_SIZE - dev->count;
	if (avail == 0) {
		ret = -ENOSPC;
		goto out;
	}

	count = min(count, avail);

	if (dev->head + count <= BUF_SIZE) {
		if (copy_from_user(dev->buf + dev->head, ubuf, count)) {
			ret = -EFAULT;
			goto out;
		}
	} else {
		size_t first  = BUF_SIZE - dev->head;
		size_t second = count - first;

		if (copy_from_user(dev->buf + dev->head, ubuf, first) ||
		    copy_from_user(dev->buf, ubuf + first, second)) {
			ret = -EFAULT;
			goto out;
		}
	}

	dev->head   = (dev->head + count) % BUF_SIZE;
	dev->count += count;
	ret         = count;

out:
	mutex_unlock(&dev->lock);
	return ret;
}

static const struct file_operations dummy_fops = {
	.owner   = THIS_MODULE,
	.open    = dummy_open,
	.release = dummy_release,
	.read    = dummy_read,
	.write   = dummy_write,
};

/* ------------------------------------------------------------------ */

static int __init dummy_init(void)
{
	int ret, i;

	if (num_devices < 1 || num_devices > 16) {
		pr_err("%s: num_devices must be between 1 and 16\n", DRIVER_NAME);
		return -EINVAL;
	}

	ret = alloc_chrdev_region(&dev_base, 0, num_devices, DRIVER_NAME);
	if (ret < 0) {
		pr_err("%s: alloc_chrdev_region failed: %d\n", DRIVER_NAME, ret);
		return ret;
	}

	dummy_class = class_create(CLASS_NAME);
	if (IS_ERR(dummy_class)) {
		ret = PTR_ERR(dummy_class);
		pr_err("%s: class_create failed: %d\n", DRIVER_NAME, ret);
		goto err_unreg_region;
	}

	devices = kcalloc(num_devices, sizeof(*devices), GFP_KERNEL);
	if (!devices) {
		ret = -ENOMEM;
		goto err_destroy_class;
	}

	for (i = 0; i < num_devices; i++) {
		struct dummy_dev *d = &devices[i];

		d->buf = kzalloc(BUF_SIZE, GFP_KERNEL);
		if (!d->buf) {
			ret = -ENOMEM;
			goto err_cleanup_devs;
		}

		mutex_init(&d->lock);
		cdev_init(&d->cdev, &dummy_fops);
		d->cdev.owner = THIS_MODULE;

		ret = cdev_add(&d->cdev, MKDEV(MAJOR(dev_base), i), 1);
		if (ret) {
			pr_err("%s: cdev_add failed for minor %d: %d\n",
			       DRIVER_NAME, i, ret);
			kfree(d->buf);
			goto err_cleanup_devs;
		}

		if (IS_ERR(device_create(dummy_class, NULL,
					 MKDEV(MAJOR(dev_base), i),
					 NULL, "dummy%d", i))) {
			pr_warn("%s: device_create failed for minor %d\n",
				DRIVER_NAME, i);
		}
	}

	pr_info("%s: loaded — major %d, %d device(s)\n",
		DRIVER_NAME, MAJOR(dev_base), num_devices);
	return 0;

err_cleanup_devs:
	while (--i >= 0) {
		device_destroy(dummy_class, MKDEV(MAJOR(dev_base), i));
		cdev_del(&devices[i].cdev);
		kfree(devices[i].buf);
	}
	kfree(devices);
err_destroy_class:
	class_destroy(dummy_class);
err_unreg_region:
	unregister_chrdev_region(dev_base, num_devices);
	return ret;
}

static void __exit dummy_exit(void)
{
	int i;

	for (i = 0; i < num_devices; i++) {
		device_destroy(dummy_class, MKDEV(MAJOR(dev_base), i));
		cdev_del(&devices[i].cdev);
		kfree(devices[i].buf);
	}
	kfree(devices);
	class_destroy(dummy_class);
	unregister_chrdev_region(dev_base, num_devices);

	pr_info("%s: unloaded\n", DRIVER_NAME);
}

module_init(dummy_init);
module_exit(dummy_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Phison Prep");
MODULE_DESCRIPTION("Dummy character device driver — study skeleton");
MODULE_VERSION("1.0");
