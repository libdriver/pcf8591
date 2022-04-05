[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver PCF8591

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue)](https://www.libdriver.com/docs/ws2812b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCF8591は、4つのアナログ入力、1つのアナログ出力、およびシリアルI²Cバスインターフェイスを備えた、シングルチップ、シングルサプライ、低電力の8ビットCMOSデータ収集デバイスです。 3つのアドレスピンA0、A1、およびA2は、ハードウェアアドレスをプログラムするために使用され、I²Cバスに接続された最大8つのデバイスを追加のハードウェアなしで使用できるようにします。 アドレス、制御、およびデータは、2線式の双方向I²Cバスを介してデバイスとの間でシリアルに転送されます。 デバイスの機能には、アナログ入力多重化、オンチップトラックアンドホールド、8ビットアナログ-デジタル変換、および8ビットデジタル-アナログ変換が含まれます。 最大スルーレートは、I²Cバスの最大速度によって決まります。 PCF8591は、閉ループ制御システムのアナログ取得、リモートデータ取得用の低電力コンバータ、バッテリ駆動機器、およびカーオーディオTVアプリケーションに使用されます。

LibDriver PCF8591は、LibDriverによって導入されたPCF8591のフル機能のドライバーであり、AD読み取り、DA出力、AD連続読み取りなどの機能を提供し、MISRA標準に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example write](#example-write)
    - [example increment](#example-increment)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver PCF8591のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver PCF8591用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver PCF8591ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver PCF8591プログラミング例が含まれています。

/ docディレクトリには、LibDriver PCF8591オフラインドキュメントが含まれています。

/ datasheetディレクトリには、PCF8591データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/ srcディレクトリ、/ interfaceディレクトリ、および/exampleディレクトリをプロジェクトに追加します。

### 使用

#### example write

```C
uint8_t res;
uint32_t i;
static uint32_t gs_rgb[21]; 
static uint8_t gs_temp[1024];

/* init */
res = ws2812b_basic_init();
if (res)
{
    return 1;
}

/* write color */
for (i = 0; i < 21; i++)
{
    gs_rgb[i] = color;
}

/* write data */
res = ws2812b_basic_write(gs_rgb, 21, gs_temp, 1024);
if (res)
{
    ws2812b_basic_deinit();

    return 1;
}

/* close the chip */
res = ws2812b_basic_deinit();
if (res)
{
    return 1;
}
else
{
    return 0;
}
```

#### example increment

```c
uint8_t res;
int16_t raws[4];
float adcs[4];
uint8_t len;
uint8_t i, j;

res = pcf8591_increment_init(PCF8591_ADDRESS_A000, PCF8591_MODE_AIN0123_GND);
if (res)
{
    pcf8591_interface_debug_print("pcf8591: init failed.\n");

    return 1;

}

...

res = pcf8591_increment_write(1.8f);
if (res)
{
    pcf8591_interface_debug_print("pcf8591: write failed.\n");
    pcf8591_basic_deinit();

    return 1;

}

...

/* read prev data */
len = 4;
res = pcf8591_increment_read((int16_t *)raws, (float *)adcs, (uint8_t *)&len);
if (res)
{
    pcf8591_interface_debug_print("pcf8591: increment read failed.\n");
    pcf8591_increment_deinit();

    return 1;

}
pcf8591_interface_delay_ms(1000);
for (i = 0; i < 3; i++)
{
    /* read data */
    len = 4;
    res = pcf8591_increment_read((int16_t *)raws, (float *)adcs, (uint8_t *)&len);
    if (res)
    {
        pcf8591_interface_debug_print("pcf8591: read failed.\n");
        pcf8591_increment_deinit();

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

pcf8591_increment_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: https://www.libdriver.com/docs/pcf8591/index.html

オフラインドキュメント: /doc/html/index.html

### 貢献

お問い合わせくださいlishifenging@outlook.com

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com