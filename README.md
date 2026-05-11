# 群聯 (Phison) 韌體工程師｜兩年面試準備計畫

> **目標**：24 個月內拿到群聯韌體 / NAND controller 工程師 offer
> **核心主軸**：C + 嵌入式 + 儲存協定 + NAND flash management
> **每週投入**：平日 2 小時 + 假日 6 小時 ≒ 16 hr/week

-----

## 📊 總體進度檢核表

|階段|月份   |主題         |關鍵產出                        |
|--|-----|-----------|----------------------------|
|Q1|1–3  |C 語言 & 資料結構|LeetCode 60 題、手刻 DS library |
|Q2|4–6  |OS & 計算機結構 |OS project、CSAPP lab 3 個    |
|Q3|7–9  |嵌入式實作      |2 個 STM32 專案 + FreeRTOS     |
|Q4|10–12|儲存入門       |NAND 筆記、讀完 3 份 datasheet    |
|Q5|13–15|進階儲存協定     |NVMe / UFS 讀書報告、ECC 實作      |
|Q6|16–18|FTL 與實戰專案  |Mini FTL simulator on GitHub|
|Q7|19–21|刷題 + 履歷    |LeetCode 180 題、3 版履歷        |
|Q8|22–24|面試衝刺       |10 場 mock、投遞 + 錄取           |

-----

## 🧱 第一年：基礎建構

### Q1 (月 1–3)｜C 語言與資料結構

**核心目標**：讓 C 變成肌肉記憶,指標與記憶體模型滾瓜爛熟。

#### 月 1：C 基礎 + 指標

- 讀 K&R《The C Programming Language》Ch 1–5
- 每日任務:寫 1 支含指標的小程式 (30 分鐘)
- 重點:`*`、`&`、`->`、指標算術、陣列 vs 指標差異
- 產出:**指標 100 題** (PTT Tech_Job 考古題)

#### 月 2：記憶體、struct、bit ops

- 讀 K&R Ch 6–8 + CSAPP Ch 2 (bit manipulation)
- 專題:
  - `malloc` / `free` 自己刻一版 (first-fit allocator)
  - struct padding & alignment 實驗,用 `offsetof` 驗證
  - `volatile` / `const` / `static` / `extern` 全部搞懂
- **必練 bit ops**：count bits、swap without temp、找唯一奇數次元素、bit reverse、power of 2 判斷

#### 月 3：資料結構手刻 (全用 C)

- Linked list (單向、雙向、circular)
- Stack / Queue (array + linked list 兩版)
- Binary tree / BST / heap
- Hash table (open addressing + chaining 各一版)
- LeetCode：**Easy 40 題 + Medium 20 題**,全用 C

**Q1 檢核點 (月 3 月底)**：

- [ ] K&R 讀完 Ch 1–8 並做完練習題
- [ ] 手刻 DS library (.c / .h) 放上 GitHub
- [ ] LeetCode 60 題 (C 語言)
- [ ] 能在白板上 10 分鐘內寫出 reverse linked list、detect cycle、merge sort

-----

### Q2 (月 4–6)｜作業系統與計算機結構

**核心目標**:理解 firmware 運行的底層環境。

#### 月 4：計算機結構

- 讀 CSAPP Ch 3–6 (machine code, processor, memory hierarchy)
- 重點:cache (set-associative, write-back / through)、virtual memory、pipeline、branch prediction
- Lab：**CSAPP Data Lab + Bomb Lab**
- ARM 架構入門:Cortex-M3 / M4 programmer's model、exception、NVIC

#### 月 5：作業系統

- 讀 OSTEP (Operating Systems: Three Easy Pieces) Part I–II
- 重點:process / thread、context switch、scheduling、mutex / semaphore / spinlock、deadlock
- Lab:xv6 或 MIT 6.828 的前 2 個 lab
- 每日 15 分鐘:OS 面試題庫

#### 月 6：同步、中斷、RTOS 概念

- 讀 OSTEP Part III (concurrency)
- 重點:生產者消費者、reader / writer lock、priority inversion、priority inheritance
- 中斷處理:ISR 設計原則、top half / bottom half、何時該 disable interrupt
- 讀 FreeRTOS reference manual 前 3 章

**Q2 檢核點 (月 6 月底)**：

- [ ] CSAPP 主要 lab 完成 3 個
- [ ] 能白板畫出 MESI cache coherence
- [ ] 能解釋 priority inversion 並舉 Mars Pathfinder 案例
- [ ] LeetCode 累計 100 題

-----

### Q3 (月 7–9)｜嵌入式實作

**核心目標**:把理論落地到硬體,建立作品集。

**硬體採購清單** (約 NT$ 3,000–5,000)：

- STM32 Nucleo-F446RE 或 Nucleo-F767ZI
- ST-Link V2 (Nucleo 內建)
- Saleae Logic 8 clone (約 NT$ 500)
- 麵包板 + 跳線 + LED + 按鈕 + 電阻
- 選配:邏輯分析儀 24MHz 版、數位電表

#### 月 7：STM32 基礎 + 週邊

- HAL 或 LL library 起手
- 完成:GPIO、UART printf redirect、SPI (OLED)、I2C (BMP280)、ADC、Timer + PWM、DMA
- **專案 1**:環境監測器 (UART 輸出 JSON)

#### 月 8：FreeRTOS

- 讀《Mastering the FreeRTOS Real Time Kernel》
- 練:task、queue、semaphore、mutex、event group、software timer
- **專案 2**:多工命令列終端 (UART task + sensor task + log task)

#### 月 9：進階 debug + 整合

- GDB + OpenOCD 單步 debug
- 用 Saleae 抓 SPI / I2C 波形、手動解碼
- 整合 **專案 3**:小型 bootloader (IAP over UART)
- 寫 README + 架構圖放 GitHub

**Q3 檢核點 (月 9 月底)**：

- [ ] GitHub 上有 3 個 embedded repo (README 完整)
- [ ] 能解釋自己每行程式碼在哪個 memory region
- [ ] 會用 `.map` 檔分析 flash / RAM 用量
- [ ] 熟悉 linker script 基本寫法

-----

### Q4 (月 10–12)｜儲存入門

**核心目標**:進入群聯主場,建立 NAND 與儲存協定底子。

#### 月 10：NAND Flash 物理與架構

- 讀 Micron《NAND Flash 101》技術文件
- 讀 Samsung、Kioxia NAND datasheet 各一份
- 重點概念:
  - SLC / MLC / TLC / QLC / 3D NAND
  - Page / Block / Plane / LUN / Die
  - Program / Read / Erase 時序與電壓
  - P/E cycle、retention、read disturb、program disturb
  - ONFI / Toggle DDR interface
- 產出:**一份自己整理的 NAND 筆記 (10 頁)**

#### 月 11：FTL 概念

- 讀論文:
  - "A Survey of Flash Translation Layer" (Chung et al.)
  - "DFTL: A Flash Translation Layer…" (Gupta et al.)
- 核心主題:
  - Mapping:page-level / block-level / hybrid
  - Garbage collection 策略 (greedy, cost-benefit)
  - Wear leveling (dynamic / static)
  - Bad block management
  - Write amplification factor (WAF)
  - Over-provisioning
- 產出:**FTL 架構白板圖**,能向外行人解釋 15 分鐘

#### 月 12：傳統協定

- USB mass storage (BOT)
- SD card (SPI mode + SD bus)
- eMMC (JEDEC 5.1)
- SATA AHCI 概念
- 讀 spec 不用全讀,抓 command set、初始化流程、error handling

**Q4 檢核點 (月 12 月底)**：

- [ ] 能解釋「為什麼 SSD 需要 FTL,HDD 不需要」
- [ ] 能算 WAF 與 OP 對壽命的影響
- [ ] 熟悉 eMMC 初始化流程 7 個狀態
- [ ] 開始關注 StorageReview、AnandTech SSD 評測

-----

## 🚀 第二年：專精與面試衝刺

### Q5 (月 13–15)｜進階儲存協定

#### 月 13：PCIe 基礎

- 讀《PCI Express Technology 3.0》Mindshare (挑 Ch 1–6)
- 重點:TLP、lane training (LTSSM)、flow control、MSI / MSI-X
- 懂 Gen3 / Gen4 / Gen5 bandwidth 計算

#### 月 14：NVMe 深入

- NVMe 2.0 spec 必讀章節:Admin / IO command、Queue pair、Namespace、SGL vs PRP
- 讀 Linux kernel `drivers/nvme/host/pci.c` 的 submit 與 completion flow
- 實作:用 `libnvme` 或 nvme-cli 玩你的 SSD,trace admin commands
- UFS 快速掃過:MIPI M-PHY、UniPro、UFS command

#### 月 15：ECC 與錯誤處理

- BCH code 原理 + 實作 (C 語言)
- LDPC 概念 (hard / soft decoding、min-sum)
- RAID-like (如 RAIN) 在 SSD 上的應用
- Read retry、read threshold calibration
- 專題:寫一個簡易 BCH encoder / decoder (256-bit data, t=4)

**Q5 檢核點 (月 15 月底)**：

- [ ] 能手畫 NVMe SQ / CQ doorbell 流程
- [ ] 能解釋為何現代 NAND 走 LDPC 不走 BCH
- [ ] 看得懂 `nvme-cli id-ctrl` 輸出每個欄位

-----

### Q6 (月 16–18)｜實戰專案

**核心目標**:一個讓面試官眼睛一亮的 portfolio 專案。

#### 月 16–17：Mini FTL Simulator (C 專案)

目標架構:

- 輸入:trace file (LBA, size, read / write)
- 模組:
1. Host interface layer (接 trace)
1. Mapping table (page-level, with cache)
1. GC engine (可切換 greedy / cost-benefit)
1. Wear leveling
1. Bad block management
1. NAND simulator (模擬 read / program / erase latency)
- 輸出:WAF、throughput、GC 次數、block erase 分布圖 (gnuplot)
- **Bonus**:用 FIO trace 跑 fio 典型 workload

README 要寫清楚:動機、架構、結果 (附圖表)、未來改進。

#### 月 18：Linux NVMe driver 研讀 + 小 patch

- 閱讀 `drivers/nvme/host/` 全部檔案
- 嘗試 build kernel 並在 VM 或 QEMU 上跑
- 做一個小修改 (加 printk 觀察 command flow 也算)
- 寫 blog post / GitHub issue 記錄

**Q6 檢核點 (月 18 月底)**：

- [ ] GitHub 主打專案 (mini FTL) 有 10+ star 或至少結構完整
- [ ] 能 20 分鐘 live demo 該專案
- [ ] 寫過至少 1 篇技術 blog

-----

### Q7 (月 19–21)｜刷題 + 履歷 + 公司研究

#### 月 19：演算法強化

- LeetCode 衝到 **180 題**,重點分布:
  - Array / String：40
  - Linked List：20
  - Tree / Graph：30
  - DP：25
  - Bit manipulation：15
  - 設計題 (LRU, LFU)：10
  - 其他：40
- 每日 2–3 題 + 每週檢討錯題

#### 月 20：系統設計 + 行為題

- 讀《Designing Data-Intensive Applications》Ch 3 (storage engine)
- 練儲存系統設計題:
  - 設計一個 key-value store (LSM-tree)
  - 設計一個 SSD wear leveling 演算法
  - 設計一個 garbage collector
- 行為題 STAR 法:準備 **10 個故事** (專案困難、衝突、失敗、學習、領導、主動)

#### 月 21：群聯公司研究 + 履歷

- 公司產品線:
  - PS5026-E26 (PCIe Gen5)、PS5021-E21T (DRAM-less)
  - UFS controller (PS8266)
  - USB flash controller
  - 企業級 Pascari
- 讀群聯近 2 年:
  - 法說會簡報 (investor.phison.com)
  - 新聞稿 + 技術白皮書
  - CEO 潘健成受訪文章
- PTT Tech_Job、面試趣、Glassdoor 搜「群聯」面試心得 (至少 20 篇)
- **履歷**:中英文各一版,經過 3 輪 review (朋友、學長姐、LinkedIn)

**Q7 檢核點 (月 21 月底)**：

- [ ] LeetCode 180+ 題
- [ ] 能寫 3 種 FTL 設計 pros / cons 比較
- [ ] 履歷定稿,GitHub / LinkedIn 全部更新
- [ ] 確認 5 個以上內推管道

-----

### Q8 (月 22–24)｜面試衝刺

#### 月 22：Mock Interview

- 技術 mock 5 場 (找學長姐、或付費 interviewing.io)
- 行為 mock 3 場
- 白板實作 mock 2 場 (專注 bug-free C code)

#### 月 23：投遞 + 一面二面

- 主動投遞群聯 + 併投:威剛、慧榮、銘旺、聯詠、瑞昱、聯發科 firmware 組 (墊場 + 備案)
- 每次面試後 24 小時內寫檢討筆記
- 常見群聯關卡:
1. 履歷 + 線上測驗 (C 程式 + 邏輯)
1. 一面技術 (直屬主管 + 資深工程師)
1. 二面技術 + HR
1. 薪資談判

#### 月 24：Offer + 談判

- 多 offer 並進,讓議價有籌碼
- 群聯薪資參考 (2024–2025)：
  - 新鮮人碩士 firmware:年薪約 120–160 萬 (含分紅)
  - 有相關經驗:180 萬 +
- 注意:群聯加班文化較重、分紅占比高,談判時確認 base vs bonus 比例

-----

## 📚 核心資源清單

### 必讀書

1. Kernighan & Ritchie《The C Programming Language》
1. Bryant & O'Hallaron《Computer Systems: A Programmer's Perspective》(CSAPP)
1. Remzi《Operating Systems: Three Easy Pieces》(免費線上)
1. Barry《Mastering the FreeRTOS Real Time Kernel》(免費)
1. Corbet《Linux Device Drivers, 3rd Edition》(免費)
1. Kleppmann《Designing Data-Intensive Applications》

### 技術文件 (免費)

- Micron TN-29 系列 NAND 技術筆記
- Samsung / Kioxia NAND datasheets
- JEDEC eMMC 5.1 spec
- NVMe spec (nvmexpress.org)
- ONFI spec (onfi.org)

### 影片課程

- MIT 6.S081 Operating Systems
- CMU 15-213 (CSAPP 配套)
- FastBit Embedded Brain Academy (Udemy) STM32 系列

### 社群 + 情報

- PTT Tech_Job 板 (台灣面試考古題第一站)
- LinkedIn:追蹤 10 個群聯 / 慧榮員工
- Reddit r/embedded、r/AskElectronics
- Hacker News (儲存相關討論)

-----

## 🎯 群聯面試高頻題型 (自備題庫)

### C 語言題

- 實作 `strcpy`、`memcpy`、`memmove` (注意 overlap)
- 實作 circular buffer 給 ISR 用
- Endian check、bit reverse
- 找記憶體 bug:給 code 挑錯
- `volatile` 什麼時候必要?
- `static` 三種用法
- struct padding 計算

### 嵌入式題

- UART 中斷處理 top / bottom half
- SPI vs I2C 差異、什麼情境選哪個
- DMA 搬資料時 cache 要注意什麼
- Bootloader 如何 jump 到 application
- Linker script `.text` `.data` `.bss` 怎麼擺

### 儲存題

- NAND 為什麼要 erase before write
- Wear leveling 怎麼做
- Write amplification 定義與降低方法
- GC 什麼時候觸發、會不會影響讀寫 latency
- Read disturb 機制、如何緩解
- Power loss protection (PLP) 設計
- Host write vs NAND write

### 行為題

- 最困難的 debug 經驗
- 跟同事技術觀點衝突怎麼處理
- 對群聯加班文化看法 (誠實但正向)
- 為什麼選群聯不選慧榮 / 威剛

-----

## ⚠️ 風險與備案

|風險           |應對                              |
|-------------|--------------------------------|
|工作 / 學業太忙進度落後|每季底留 2 週 buffer,砍次要項目 (如 UFS 細節)|
|群聯當年不缺人      |同步投慧榮、銘旺、威剛、群聯海外分公司             |
|技術面表現差       |多投幾間 SSD 廠累積實戰,6 個月後再戰          |
|薪資不如預期       |拿其他 offer 議價;或先進去 1–2 年再跳       |

-----

## 🔁 每週固定節奏

- **週一–五 (每日 2 小時)**:主教材 1hr + LeetCode 1hr
- **週六 (6 小時)**:專案 / lab 實作
- **週日 (3 小時 + 休息)**:複習 + 寫週報 (回顧進度、下週計畫)
- **每月最後一天**:對照檢核表打勾,寫月報放 GitHub README

-----

**最後提醒**:群聯重視 **肯做、抗壓、C 扎實、懂 NAND 特性** 這四點。計畫再完美,執行才是一切。從今天開始。
