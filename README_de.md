[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver PCF8591
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ws2812b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der PCF8591 ist ein Single-Chip-Single-Supply-Low-Power-8-Bit-CMOS-Datenerfassungsgerät mit vier analogen Eingängen, einem analogen Ausgang und einer seriellen I2C-Bus-Schnittstelle.Drei Adress-Pins A0, A1 und A2 werden zur Programmierung verwendet Hardware-Adresse, die den Einsatz von bis zu acht an den I2C-Bus angeschlossenen Geräten ohne zusätzliche Hardware ermöglicht.Adresse, Steuerung und Daten zum und vom Gerät werden seriell über den zweiadrigen, bidirektionalen I2C-Bus übertragen.Zu den Funktionen des Geräts gehören: analoges Eingangs-Multiplexing, On-Chip-Track-and-Hold-Funktion, 8-Bit-Analog-Digital-Wandlung und eine 8-Bit-Digital-Analog-Wandlung Die maximale Wandlungsrate ist durch die maximale Geschwindigkeit des I2C-Busses gegeben.PCF8591 wird in Closed-Loop-Steuerungssystemen, Low-Power-Konvertern für die Ferndatenerfassung, batteriebetriebenen Geräten und analogen Erfassungen in Automobil-Audio-TV-Anwendungen verwendet.

LibDriver PCF8591 ist ein voll funktionsfähiger Treiber von PCF8591, der von LibDriver gestartet wurde. Er bietet AD-Lesen, DA-Ausgabe, kontinuierliches AD-Lesen und andere Funktionen, und LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example write](#example-write)
    - [example increment](#example-increment)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver PCF8591-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver PCF8591 IIC。

/test enthält den Testcode des LibDriver PCF8591-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen。

/example enthält LibDriver PCF8591-Beispielcode.

/doc enthält das LibDriver PCF8591-Offlinedokument.

/Datenblatt enthält PCF8591-Datenblatt。

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie /src, /interface und /example zu Ihrem Projekt hinzu.

### Nutzung

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

### Dokument

Online-Dokumente: https://www.libdriver.com/docs/pcf8591/index.html

Offline-Dokumente: /doc/html/index.html

### Beitrag

Bitte senden Sie eine E-Mail an lishifenging@outlook.com

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com