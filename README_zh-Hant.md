[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCF8591

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pcf8591/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCF8591是一款單芯片、單電源、低功率8位CMOS數據採集器件，帶有四個模擬輸入、一個模擬輸出和一個串行I²C總線接口。三個地址引腳A0、A1和A2用於編程硬件地址，允許使用最多八個連接至I²C總線的器件而無需額外硬件。通過兩線雙向I²C總線將地址、控制和數據串行傳送至器件或從器件串行傳送。器件功能包括模擬輸入多路復用、片上跟踪和保持功能、8位模擬-數字轉換和8位數字-模擬轉換。最大轉換速率由I²C總線的最大速度決定。 PCF8591被用於閉環控制系統、遠程數據採集的低功率轉換器、電池供電設備和汽車音響電視機應用中的模擬採集。

LibDriver PCF8591是LibDriver推出的PCF8591的全功能驅動，該驅動提供AD讀取、DA輸出、AD連續讀取等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example increment](#example-increment)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver PCF8591的源文件。

/interface目錄包含了LibDriver PCF8591與平台無關的IIC總線模板。

/test目錄包含了LibDriver PCF8591驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver PCF8591編程範例。

/doc目錄包含了LibDriver PCF8591離線文檔。

/datasheet目錄包含了PCF8591數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

#### example basic

```C
#include "driver_pcf8591_basic.h"

uint8_t res;
uint8_t i;
int16_t raw;
float adc;

res = pcf8591_basic_init(PCF8591_ADDRESS_A000, PCF8591_MODE_AIN0123_GND);
if (res != 0)
{
    pcf8591_interface_debug_print("pcf8591: init failed.\n");

    return 1;
}

...

res = pcf8591_basic_write(1.2f);
if (res != 0)
{
    pcf8591_interface_debug_print("pcf8591: write failed.\n");
    (void)pcf8591_basic_deinit();

    return 1;
}

...

res = pcf8591_basic_set_channel(PCF8591_CHANNEL_0);
if (res != 0)
{
    pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
    (void)pcf8591_basic_deinit();

    return 1;
}

...

/* read prev data */
res = pcf8591_basic_read((int16_t *)&raw, (float *)&adc);
if (res != 0)
{
    pcf8591_interface_debug_print("pcf8591: read failed.\n");
    (void)pcf8591_basic_deinit();

    return 1;
}
pcf8591_interface_delay_ms(1000);
for (i = 0; i < 3; i++)
{
    /* read data */
    res = pcf8591_basic_read((int16_t *)&raw, (float *)&adc);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: read failed.\n");
        (void)pcf8591_basic_deinit();

        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adc);
    pcf8591_interface_delay_ms(1000);
    
    ...
    
}

...

(void)pcf8591_basic_deinit();

return 0;
```

#### example increment

```C
#include "driver_pcf8591_increment.h"

uint8_t res;
int16_t raws[4];
float adcs[4];
uint8_t len;
uint8_t i, j;

res = pcf8591_increment_init(PCF8591_ADDRESS_A000, PCF8591_MODE_AIN0123_GND);
if (res != 0)
{
    pcf8591_interface_debug_print("pcf8591: init failed.\n");

    return 1;
}

...

res = pcf8591_increment_write(1.8f);
if (res != 0)
{
    pcf8591_interface_debug_print("pcf8591: write failed.\n");
    (void)pcf8591_basic_deinit();

    return 1;
}

...

/* read prev data */
len = 4;
res = pcf8591_increment_read((int16_t *)raws, (float *)adcs, (uint8_t *)&len);
if (res != 0)
{
    pcf8591_interface_debug_print("pcf8591: increment read failed.\n");
    (void)pcf8591_increment_deinit();

    return 1;
}
pcf8591_interface_delay_ms(1000);
for (i = 0; i < 3; i++)
{
    /* read data */
    len = 4;
    res = pcf8591_increment_read((int16_t *)raws, (float *)adcs, (uint8_t *)&len);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: read failed.\n");
        (void)pcf8591_increment_deinit();

        return 1;
    }
    for (j = 0; j < len; j++)
    {
        pcf8591_interface_debug_print("pcf8591: raw is %d.\n", raws[j]);
        pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adcs[j]);
        
        ...
        
    }
    pcf8591_interface_delay_ms(1000);
    
    ...
    
}

...

(void)pcf8591_increment_deinit();

return 0;
```

### 文檔

在線文檔: [https://www.libdriver.com/docs/pcf8591/index.html](https://www.libdriver.com/docs/pcf8591/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。