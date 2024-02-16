[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCF8591

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pcf8591/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCF8591은 4개의 아날로그 입력, 1개의 아날로그 출력 및 직렬 I2C 버스 인터페이스가 있는 단일 칩, 단일 공급 저전력 8비트 CMOS 데이터 수집 장치입니다.3개의 주소 핀 A0, A1 및 A2는 프로그래밍에 사용됩니다. 추가 하드웨어 없이 I2C 버스에 연결된 최대 8개의 장치를 사용할 수 있는 하드웨어 주소 장치와 주고받는 주소, 제어 및 데이터는 2라인 양방향 I2C 버스를 통해 직렬로 전송됩니다. 장치의 기능은 다음과 같습니다. 아날로그 입력 다중화, 온칩 트랙 및 홀드 기능, 8비트 아날로그-디지털 변환 및 8비트 디지털-아날로그 변환 최대 변환 속도는 I2C 버스의 최대 속도에 의해 지정됩니다.PCF8591 폐루프 제어 시스템, 원격 데이터 수집을 위한 저전력 컨버터, 배터리 구동 장비 및 자동차 오디오 TV 애플리케이션의 아날로그 수집에 사용됩니다.

LibDriver PCF8591은 LibDriver에서 출시한 PCF8591의 전체 기능 드라이버입니다. AD 읽기, DA 출력, AD 연속 읽기 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example write](#example-write)
    - [example increment](#example-increment)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver PCF8591의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver PCF8591용 플랫폼 독립적인 IIC 버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver PCF8591드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver PCF8591프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver PCF8591오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 PCF8591데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 IIC 버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC 버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

#### example write

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

```c
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

### 문서

온라인 문서: [https://www.libdriver.com/docs/pcf8591/index.html](https://www.libdriver.com/docs/pcf8591/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.