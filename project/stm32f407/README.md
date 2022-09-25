### 1. Chip

#### 1.1 Chip Info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

iic pin: SCL/SDA PB8/PB9.

### 2. Shell

#### 2.1 Shell Parameter

baud rate: 115200.

data bits : 8.

stop bits: 1.

parity: none.

flow control: none.

### 3. PCF8591

#### 3.1 Command Instruction

​          pcf8591 is a basic command which can test all pcf8591 driver function:

​           -i        show pcf8591 chip and driver information.

​           -h       show pcf8591 help.

​           -p       show pcf8591 pin connections of the current board.

​           -t  (reg -a  (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) | readwrite <times> -a  (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) )

​           -t reg -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)        run pcf8591 register test. 

​           -t readwrite <times> -a  (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)        run pcf8591 read write test.times means test times.

​           -c basic (-i <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)  -m (AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3) -ch (0 | 1 | 2 | 3) | -o <dac> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7))

​           -c basic -i <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)  -m (AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3) -ch (0 | 1 | 2 | 3)         run pcf8591 read function.times means read times.

​           -c basic -o <dac> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)        run pcf8591 write function.dac means output value.

​           -c increment (-i <times>  -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3) | -o <dac> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) )

​           -c increment -i <times>  -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3)        run pcf8591 increment function.times means read times.

​           -c increment -o <dac> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)        run pcf8591 write function.dac means output value.

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
pcf8591 -t reg -a 0

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
pcf8591: check reference voltage ok.
pcf8591: pcf8591_dac_convert_to_register test.
pcf8591: set convert voltage 0.670.
pcf8591: check register 0x66.
pcf8591: finish register test.
```

```shell
pcf8591 -t readwrite 3 -a 0 

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
pcf8591: raw is 34.
pcf8591: adc is 0.438.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
pcf8591: raw is 128.
pcf8591: adc is 1.650.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
pcf8591: raw is 146.
pcf8591: adc is 1.882.
pcf8591: raw is 34.
pcf8591: adc is 0.438.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
pcf8591: raw is 146.
pcf8591: adc is 1.882.
pcf8591: set mode AIN012_AIN3.
pcf8591: raw is 127.
pcf8591: adc is 1.637.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is -110.
pcf8591: adc is -1.418.
pcf8591: raw is 127.
pcf8591: adc is 1.637.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 127.
pcf8591: adc is 1.637.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: set mode AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN.
pcf8591: raw is 146.
pcf8591: adc is 1.882.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 146.
pcf8591: adc is 1.882.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 146.
pcf8591: adc is 1.882.
pcf8591: raw is 33.
pcf8591: adc is 0.425.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: set mode AIN0_AIN1_AND_ANI2_AIN3.
pcf8591: raw is 113.
pcf8591: adc is 1.457.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 113.
pcf8591: adc is 1.457.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 113.
pcf8591: adc is 1.457.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: channel test.
pcf8591: set channel 0.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 144.
pcf8591: adc is 1.856.
pcf8591: raw is 144.
pcf8591: adc is 1.856.
pcf8591: set channel 1.
pcf8591: raw is 144.
pcf8591: adc is 1.856.
pcf8591: raw is 32.
pcf8591: adc is 0.412.
pcf8591: raw is 32.
pcf8591: adc is 0.412.
pcf8591: set channel 2.
pcf8591: raw is 32.
pcf8591: adc is 0.412.
pcf8591: raw is 112.
pcf8591: adc is 1.444.
pcf8591: raw is 112.
pcf8591: adc is 1.444.
pcf8591: set channel 3.
pcf8591: raw is 112.
pcf8591: adc is 1.444.
pcf8591: raw is 112.
pcf8591: adc is 1.444.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
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
pcf8591 -c basic -i 3 -a 0 -m AIN0123_GND -ch 0 

pcf8591: 1/3.
pcf8591: adc is 1.650.
pcf8591: 2/3.
pcf8591: adc is 1.882.
pcf8591: 3/3.
pcf8591: adc is 1.856.
```

```shell
pcf8591 -c basic -o 1.1 -a 0

pcf8591: write 1.100.
```

```shell
pcf8591 -c increment -i 3 -a 0 -m AIN0123_GND 

pcf8591: 1/3.
pcf8591: raw is 34.
pcf8591: adc is 0.438.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
pcf8591: raw is 146.
pcf8591: adc is 1.882.
pcf8591: 2/3.
pcf8591: raw is 34.
pcf8591: adc is 0.438.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
pcf8591: raw is 146.
pcf8591: adc is 1.882.
pcf8591: 3/3.
pcf8591: raw is 34.
pcf8591: adc is 0.438.
pcf8591: raw is 120.
pcf8591: adc is 1.547.
pcf8591: raw is 0.
pcf8591: adc is 0.000.
pcf8591: raw is 146.
pcf8591: adc is 1.882.
```

```shell
pcf8591 -c increment -o 1.1 -a 0

pcf8591: write 1.100.
```

```shell
pcf8591 -h

pcf8591 -i
	show pcf8591 chip and driver information.
pcf8591 -h
	show pcf8591 help.
pcf8591 -p
	show pcf8591 pin connections of the current board.
pcf8591 -t reg -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)
	run pcf8591 register test.run pcf8591 register test.
pcf8591 -t readwrite <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)
	run pcf8591 read write test.times means test times.
pcf8591 -c basic -i <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3) -ch (0 | 1 | 2 | 3)
	run pcf8591 read function.times means read times.
pcf8591 -c basic -o <dac> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)
	run pcf8591 write function.dac means output value.
pcf8591 -c increment -i <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3)
	run pcf8591 increment function.times means read times.
pcf8591 -c increment -o <dac> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)
	run pcf8591 write function.dac means output value.
```

