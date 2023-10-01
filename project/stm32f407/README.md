### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. PCF8591

#### 3.1 Command Instruction

1. Show pcf8591 chip and driver information.

   ```shell
   pcf8591 (-i | --information)
   ```

2. Show pcf8591 help.

   ```shell
   pcf8591 (-h | --help)
   ```

3. Show pcf8591 pin connections of the current board.

   ```shell
   pcf8591 (-p | --port)
   ```

4. Run pcf8591 register test.

   ```shell
   pcf8591 (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
   ```

5. Run pcf8591 read write test, num means test times.

   ```shell
   pcf8591 (-t readwrite | --test=readwrite) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
   ```

6. Run pcf8591 read function, num means read times.

   ```shell
   pcf8591 (-e basic-input | --example=basic-input) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>] [--mode=<AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3>] [--channel=<0 | 1 | 2 | 3>]
   ```

7. Run pcf8591 write function, voltage means output value.

   ```shell
   pcf8591 (-e basic-output | --example=basic-output) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] --dac=<voltage>
   ```

8. Run pcf8591 increment function, num means read times.

   ```shell
   pcf8591 (-e increment-input | --example=increment-input) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>] [--mode=<AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3>]
   ```

9. Run pcf8591 write function, voltage means output value.

   ```shell
   pcf8591 (-e increment-output | --example=increment-output) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] --dac=<voltage>
   ```

#### 3.2 Command Example

```shell
pcf8591 -i

pcf8591: chip is NXP PCF8591.
pcf8591: manufacturer is NXP.
pcf8591: interface is IIC.
pcf8591: driver version is 2.0.
pcf8591: min supply voltage is 2.5V.
pcf8591: max supply voltage is 6.0V.
pcf8591: max current is 50.00mA.
pcf8591: max temperature is 85.0C.
pcf8591: min temperature is -40.0C.
```

```shell
pcf8591 -p

pcf8591: SCL connected to GPIOB PIN8.
pcf8591: SDA connected to GPIOB PIN9.
```

```shell
pcf8591 -t reg --addr=0

pcf8591: chip is NXP PCF8591.
pcf8591: manufacturer is NXP.
pcf8591: interface is IIC.
pcf8591: driver version is 2.0.
pcf8591: min supply voltage is 2.5V.
pcf8591: max supply voltage is 6.0V.
pcf8591: max current is 50.00mA.
pcf8591: max temperature is 85.0C.
pcf8591: min temperature is -40.0C.
pcf8591: start register test.
pcf8591: pcf8591_set_addr_pin/pcf8591_get_addr_pin test.
pcf8591: set addr pin a000.
pcf8591: check addr pin ok.
pcf8591: set addr pin a001.
pcf8591: check addr pin ok.
pcf8591: set addr pin a010.
pcf8591: check addr pin ok.
pcf8591: set addr pin a011.
pcf8591: check addr pin ok.
pcf8591: set addr pin a100.
pcf8591: check addr pin ok.
pcf8591: set addr pin a101.
pcf8591: check addr pin ok.
pcf8591: set addr pin a110.
pcf8591: check addr pin ok.
pcf8591: set addr pin a111.
pcf8591: check addr pin ok.
pcf8591: pcf8591_set_channel/pcf8591_get_channel test.
pcf8591: set channel 0.
pcf8591: check channel ok.
pcf8591: set channel 1.
pcf8591: check channel ok.
pcf8591: set channel 2.
pcf8591: check channel ok.
pcf8591: set channel 3.
pcf8591: check channel ok.
pcf8591: pcf8591_set_mode/pcf8591_get_mode test.
pcf8591: set mode AIN0123_GND.
pcf8591: check mode ok.
pcf8591: set mode AIN012_AIN3.
pcf8591: check mode ok.
pcf8591: set mode AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3.
pcf8591: check mode ok.
pcf8591: set mode AIN0_AIN1_AND_ANI2_AIN3.
pcf8591: check mode ok.
pcf8591: pcf8591_set_auto_increment/pcf8591_get_auto_increment test.
pcf8591: enable auto increment.
pcf8591: check auto increment ok.
pcf8591: disable auto increment.
pcf8591: check auto increment ok.
pcf8591: pcf8591_set_reference_voltage/pcf8591_get_reference_voltage test.
pcf8591: set ref voltage 1.680.
pcf8591: check reference voltage 1.680.
pcf8591: pcf8591_dac_convert_to_register test.
pcf8591: set convert voltage 0.670.
pcf8591: check register 0x66.
pcf8591: finish register test.
```

```shell
pcf8591 -t readwrite --addr=0 --times=3

pcf8591: chip is NXP PCF8591.
pcf8591: manufacturer is NXP.
pcf8591: interface is IIC.
pcf8591: driver version is 2.0.
pcf8591: min supply voltage is 2.5V.
pcf8591: max supply voltage is 6.0V.
pcf8591: max current is 50.00mA.
pcf8591: max temperature is 85.0C.
pcf8591: min temperature is -40.0C.
pcf8591: start read write test.
pcf8591: mode test.
pcf8591: set mode AIN0123_GND.
pcf8591: raw is 161.
pcf8591: adc is 2.075.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is 116.
pcf8591: adc is 1.495.
pcf8591: raw is 127.
pcf8591: adc is 1.637.
pcf8591: raw is 162.
pcf8591: adc is 2.088.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is 115.
pcf8591: adc is 1.482.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
pcf8591: raw is 161.
pcf8591: adc is 2.075.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is 115.
pcf8591: adc is 1.482.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
pcf8591: set mode AIN012_AIN3.
pcf8591: raw is -93.
pcf8591: adc is -1.199.
pcf8591: raw is -121.
pcf8591: adc is -1.560.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
pcf8591: raw is -94.
pcf8591: adc is -1.212.
pcf8591: raw is -121.
pcf8591: adc is -1.560.
pcf8591: raw is -104.
pcf8591: adc is -1.341.
pcf8591: raw is -93.
pcf8591: adc is -1.199.
pcf8591: raw is -121.
pcf8591: adc is -1.560.
pcf8591: raw is -104.
pcf8591: adc is -1.341.
pcf8591: set mode AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN.
pcf8591: raw is 161.
pcf8591: adc is 2.075.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is -104.
pcf8591: adc is -1.341.
pcf8591: raw is 161.
pcf8591: adc is 2.075.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is -104.
pcf8591: adc is -1.341.
pcf8591: raw is 161.
pcf8591: adc is 2.075.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is -104.
pcf8591: adc is -1.341.
pcf8591: set mode AIN0_AIN1_AND_ANI2_AIN3.
pcf8591: raw is 127.
pcf8591: adc is 1.637.
pcf8591: raw is -104.
pcf8591: adc is -1.341.
pcf8591: raw is 127.
pcf8591: adc is 1.637.
pcf8591: raw is -104.
pcf8591: adc is -1.341.
pcf8591: raw is 127.
pcf8591: adc is 1.637.
pcf8591: raw is -104.
pcf8591: adc is -1.341.
pcf8591: channel test.
pcf8591: set channel 0.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: set channel 1.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: set channel 2.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: set channel 3.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: raw is 152.
pcf8591: adc is 1.959.
pcf8591: write test.
pcf8591: adc is 2.968.
pcf8591: reg is 0xE6.
pcf8591: adc is 0.567.
pcf8591: reg is 0x2B.
pcf8591: adc is 0.709.
pcf8591: reg is 0x37.
pcf8591: finish read test.
```

```shell
pcf8591 -e basic-input --addr=0 --times=3 --mode=AIN0123_GND --channel=0

pcf8591: 1/3.
pcf8591: adc is 1.959.
pcf8591: 2/3.
pcf8591: adc is 1.959.
pcf8591: 3/3.
pcf8591: adc is 1.959.
```

```shell
pcf8591 -e basic-output --addr=0 --dac=1.1

pcf8591: write 1.100.
```

```shell
pcf8591 -e increment-input --addr=0 --times=3 --mode=AIN0123_GND

pcf8591: 1/3.
pcf8591: raw is 161.
pcf8591: adc is 2.075.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is 116.
pcf8591: adc is 1.495.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
pcf8591: 2/3.
pcf8591: raw is 161.
pcf8591: adc is 2.075.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is 116.
pcf8591: adc is 1.495.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
pcf8591: 3/3.
pcf8591: raw is 161.
pcf8591: adc is 2.075.
pcf8591: raw is 32.
pcf8591: adc is 0.412.
pcf8591: raw is 116.
pcf8591: adc is 1.495.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
```

```shell
pcf8591 -e increment-output --addr=0 --dac=1.1

pcf8591: write 1.100.
```

```shell
pcf8591 -h

Usage:
  pcf8591 (-i | --information)
  pcf8591 (-h | --help)
  pcf8591 (-p | --port)
  pcf8591 (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
  pcf8591 (-t readwrite | --test=readwrite) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
  pcf8591 (-e basic-input | --example=basic-input) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
          [--mode=<AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3>]
          [--channel=<0 | 1 | 2 | 3>]
  pcf8591 (-e basic-output | --example=basic-output) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
          --dac=<voltage>
  pcf8591 (-e increment-input | --example=increment-input) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
          [--mode=<AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3>]
  pcf8591 (-e increment-output | --example=increment-output) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
          --dac=<voltage>

Options:
      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>
                                   Set the addr pin.([default: 0])
      --channel=<0 | 1 | 2 | 3>    Set the used channel.([default: 0])
      --dac=<voltage>              Set the dac value in voltage.
  -e <basic-input | basic-output | increment-input | increment-output>, --example=<basic-input
     | basic-output | increment-input | increment-output>
                                   Run the driver example.
  -h, --help                       Show the help.
  -i, --information                Show the chip information.
      --mode=<AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3>
                                   Set the chip mode.([default: AIN0123_GND])
  -p, --port                       Display the pin connections of the current board.
  -t <reg | readwrite>, --test=<reg | readwrite>
                                   Run the driver test.
      --times=<num>                Set the running times.([default: 3])
```

