[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCF8591

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pcf8591/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCF8591是一款单芯片、单电源、低功率8位CMOS数据采集器件，带有四个模拟输入、一个模拟输出和一个串行I²C总线接口。三个地址引脚A0、A1和A2用于编程硬件地址，允许使用最多八个连接至I²C总线的器件而无需额外硬件。通过两线双向I²C总线将地址、控制和数据串行传送至器件或从器件串行传送。器件功能包括模拟输入多路复用、片上跟踪和保持功能、8位模拟-数字转换和8位数字-模拟转换。最大转换速率由I²C总线的最大速度决定。PCF8591被用于闭环控制系统、远程数据采集的低功率转换器、电池供电设备和汽车音响电视机应用中的模拟采集。

LibDriver PCF8591是LibDriver推出的PCF8591的全功能驱动，该驱动提供AD读取、DA输出、AD连续读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example increment](#example-increment)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver PCF8591的源文件。

/interface目录包含了LibDriver PCF8591与平台无关的IIC总线模板。

/test目录包含了LibDriver PCF8591驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver PCF8591编程范例。

/doc目录包含了LibDriver PCF8591离线文档。

/datasheet目录包含了PCF8591数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/pcf8591/index.html](https://www.libdriver.com/docs/pcf8591/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。