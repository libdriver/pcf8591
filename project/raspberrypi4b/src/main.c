/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-02-18
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/18  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_pcf8591_register_test.h"
#include "driver_pcf8591_read_write_test.h"
#include "driver_pcf8591_basic.h"
#include "driver_pcf8591_increment.h"
#include <stdlib.h>

/**
 * @brief     pcf8591 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t pcf8591(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            pcf8591_info_t info;
            
            /* print pcf8591 info */
            pcf8591_info(&info);
            pcf8591_interface_debug_print("pcf8591: chip is %s.\n", info.chip_name);
            pcf8591_interface_debug_print("pcf8591: manufacturer is %s.\n", info.manufacturer_name);
            pcf8591_interface_debug_print("pcf8591: interface is %s.\n", info.interface);
            pcf8591_interface_debug_print("pcf8591: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            pcf8591_interface_debug_print("pcf8591: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            pcf8591_interface_debug_print("pcf8591: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            pcf8591_interface_debug_print("pcf8591: max current is %0.2fmA.\n", info.max_current_ma);
            pcf8591_interface_debug_print("pcf8591: max temperature is %0.1fC.\n", info.temperature_max);
            pcf8591_interface_debug_print("pcf8591: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            pcf8591_interface_debug_print("pcf8591: SCL connected to GPIO3(BCM).\n");
            pcf8591_interface_debug_print("pcf8591: SDA connected to GPIO2(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show pcf8591 help */
            
            help:
            
            pcf8591_interface_debug_print("pcf8591 -i\n\tshow pcf8591 chip and driver information.\n");
            pcf8591_interface_debug_print("pcf8591 -h\n\tshow pcf8591 help.\n");
            pcf8591_interface_debug_print("pcf8591 -p\n\tshow pcf8591 pin connections of the current board.\n");
            pcf8591_interface_debug_print("pcf8591 -t reg -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)\n\trun pcf8591 register test.run pcf8591 register test.\n");
            pcf8591_interface_debug_print("pcf8591 -t readwrite <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)\n\trun pcf8591 read write test.times means test times.\n");
            pcf8591_interface_debug_print("pcf8591 -c basic -i <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (AIN0123_GND | AIN012_AIN3 | "
                                          "AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3) -ch (0 | 1 | 2 | 3)\n\t");
            pcf8591_interface_debug_print("run pcf8591 read function.times means read times.\n");
            pcf8591_interface_debug_print("pcf8591 -c basic -o <dac> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)\n\trun pcf8591 write function.dac means output value.\n");
            pcf8591_interface_debug_print("pcf8591 -c increment -i <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -m (AIN0123_GND | AIN012_AIN3 | "
                                          "AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3)\n\t");
            pcf8591_interface_debug_print("run pcf8591 increment function.times means read times.\n");
            pcf8591_interface_debug_print("pcf8591 -c increment -o <dac> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)\n\trun pcf8591 write function.dac means output value.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                pcf8591_address_t address;
                
                if (strcmp("-a", argv[3]) != 0)
                {
                    return 5;
                }
                if ((argv[4][0]<'0') || argv[4][0]>'7')
                {
                    pcf8591_interface_debug_print("pcf8591: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (pcf8591_address_t)atoi(argv[4]);
                
                /* run reg test */
                if (pcf8591_register_test(address) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* readwrite function */
            if (strcmp("readwrite", argv[2]) == 0)
            {
                pcf8591_address_t address;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if ((argv[5][0]<'0') || argv[5][0]>'7')
                {
                    pcf8591_interface_debug_print("pcf8591: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (pcf8591_address_t)atoi(argv[5]);
        
                /* run reg test */
                if (pcf8591_read_write_test(address, atoi(argv[3])) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }

            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 7)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic function */
            if (strcmp("basic", argv[2]) == 0)
            {
                uint8_t res;
                pcf8591_address_t address;

                if (strcmp("-o", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("-a", argv[5]) != 0)
                {
                    return 5;
                }
                if ((argv[6][0]<'0') || argv[6][0]>'7')
                {
                    pcf8591_interface_debug_print("pcf8591: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (pcf8591_address_t)atoi(argv[6]);
                res = pcf8591_basic_init(address, PCF8591_MODE_AIN0123_GND);
                if (res != 0)
                {
                    pcf8591_interface_debug_print("pcf8591: init failed.\n");
                    
                    return 1;
                }
                res = pcf8591_basic_write((float)atof(argv[4]));
                if (res != 0)
                {
                    pcf8591_interface_debug_print("pcf8591: write failed.\n");
                    (void)pcf8591_basic_deinit();
                    
                    return 1;
                }
                pcf8591_interface_debug_print("pcf8591: write %0.3f.\n", atof(argv[4]));
                (void)pcf8591_basic_deinit();
                
                return 0;
            }

            /* increment function */
            else if (strcmp("increment", argv[2]) == 0)
            {
                uint8_t res;
                pcf8591_address_t address;

                if (strcmp("-o", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("-a", argv[5]) != 0)
                {
                    return 5;
                }
                if ((argv[6][0]<'0') || argv[6][0]>'7')
                {
                    pcf8591_interface_debug_print("pcf8591: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (pcf8591_address_t)atoi(argv[6]);
                res = pcf8591_increment_init(address, PCF8591_MODE_AIN0123_GND);
                if (res != 0)
                {
                    pcf8591_interface_debug_print("pcf8591: init failed.\n");
                    
                    return 1;
                }
                res = pcf8591_increment_write((float)atof(argv[4]));
                if (res != 0)
                {
                    pcf8591_interface_debug_print("pcf8591: write failed.\n");
                    (void)pcf8591_increment_deinit();
                    
                    return 1;
                }
                pcf8591_interface_debug_print("pcf8591: write %0.3f.\n", atof(argv[4]));
                (void)pcf8591_increment_deinit();
                
                return 0;
            }

            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 9)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic function */
            if (strcmp("increment", argv[2]) == 0)
            {
                uint8_t res;
                int16_t raws[4];
                float adcs[4];
                uint8_t len;
                uint32_t i, j, times;
                pcf8591_mode_t mode;
                pcf8591_address_t address;

                if (strcmp("-i", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("-a", argv[5]) != 0)
                {
                    return 5;
                }
                if ((argv[6][0]<'0') || argv[6][0]>'7')
                {
                    pcf8591_interface_debug_print("pcf8591: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (pcf8591_address_t)atoi(argv[6]);
                if (strcmp("-m", argv[7]) != 0)
                {
                    return 5;
                }
                if (strcmp("AIN0123_GND", argv[8]) == 0)
                {
                    mode = PCF8591_MODE_AIN0123_GND;
                }
                else if (strcmp("AIN012_AIN3", argv[8]) == 0)
                {
                    mode = PCF8591_MODE_AIN012_AIN3;
                }
                else if (strcmp("AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3", argv[8]) == 0)
                {
                    mode = PCF8591_MODE_AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3;
                }
                else if (strcmp("AIN0_AIN1_AND_ANI2_AIN3", argv[8]) == 0)
                {
                    mode = PCF8591_MODE_AIN0_AIN1_AND_ANI2_AIN3;
                }
                else
                {
                    pcf8591_interface_debug_print("pcf8591: mode is invalid.\n");
                    
                    return 5;
                }

                res = pcf8591_increment_init(address, mode);
                if (res != 0)
                {
                    pcf8591_interface_debug_print("pcf8591: init failed.\n");
                    
                    return 1;
                }
                times = atoi(argv[4]);
                
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
                for (i=0; i<times; i++)
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
                    pcf8591_interface_debug_print("pcf8591: %d/%d.\n", i+1, times);
                    for (j=0; j<len; j++)
                    {
                        pcf8591_interface_debug_print("pcf8591: raw is %d.\n", raws[j]);
                        pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adcs[j]);
                    }
                    pcf8591_interface_delay_ms(1000);
                }
                (void)pcf8591_increment_deinit();
                
                return 0;
            }

            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 11)
    {
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* basic function */
            if (strcmp("basic", argv[2]) == 0)
            {
                uint8_t res;
                int16_t raw;
                float adc;
                uint32_t i, times;
                pcf8591_mode_t mode;
                pcf8591_channel_t channel;
                pcf8591_address_t address;

                if (strcmp("-i", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("-a", argv[5]) != 0)
                {
                    return 5;
                }
                if ((argv[6][0]<'0') || argv[6][0]>'7')
                {
                    pcf8591_interface_debug_print("pcf8591: iic address is invalid.\n");
                    
                    return 5;
                }
                address = (pcf8591_address_t)atoi(argv[6]);
                if (strcmp("-m", argv[7]) != 0)
                {
                    return 5;
                }
                if (strcmp("AIN0123_GND", argv[8]) == 0)
                {
                    mode = PCF8591_MODE_AIN0123_GND;
                }
                else if (strcmp("AIN012_AIN3", argv[8]) == 0)
                {
                    mode = PCF8591_MODE_AIN012_AIN3;
                }
                else if (strcmp("AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3", argv[8]) == 0)
                {
                    mode = PCF8591_MODE_AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3;
                }
                else if (strcmp("AIN0_AIN1_AND_ANI2_AIN3", argv[8]) == 0)
                {
                    mode = PCF8591_MODE_AIN0_AIN1_AND_ANI2_AIN3;
                }
                else
                {
                    pcf8591_interface_debug_print("pcf8591: mode is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-ch", argv[9]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[10]) == 0)
                {
                    channel = PCF8591_CHANNEL_0;
                }
                else if (strcmp("1", argv[10]) == 0)
                {
                    channel = PCF8591_CHANNEL_1;
                }
                else if (strcmp("2", argv[10]) == 0)
                {
                    channel = PCF8591_CHANNEL_2;
                }
                else if (strcmp("3", argv[10]) == 0)
                {
                    channel = PCF8591_CHANNEL_3;
                }
                else
                {
                    pcf8591_interface_debug_print("pcf8591: channel is invalid.\n");
                    
                    return 5;
                }
                res = pcf8591_basic_init(address, mode);
                if (res != 0)
                {
                    pcf8591_interface_debug_print("pcf8591: init failed.\n");
                    
                    return 1;
                }
                res = pcf8591_basic_set_channel(channel);
                if (res != 0)
                {
                    pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
                    (void)pcf8591_basic_deinit();
                    
                    return 1;
                }
                times = atoi(argv[4]);

                /* read prev data */
                res = pcf8591_basic_read((int16_t *)&raw, (float *)&adc);
                if (res != 0)
                {
                    pcf8591_interface_debug_print("pcf8591: read failed.\n");
                    (void)pcf8591_basic_deinit();
                    
                    return 1;
                }
                pcf8591_interface_delay_ms(1000);
                for (i=0; i<times; i++)
                {
                    /* read data */
                    res = pcf8591_basic_read((int16_t *)&raw, (float *)&adc);
                    if (res != 0)
                    {
                        pcf8591_interface_debug_print("pcf8591: read failed.\n");
                        (void)pcf8591_basic_deinit();
                        
                        return 1;
                    }
                    pcf8591_interface_debug_print("pcf8591: %d/%d.\n", i+1, times);
                    pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adc);
                    pcf8591_interface_delay_ms(1000);
                }
                (void)pcf8591_basic_deinit();
                
                return 0;
            }

            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* param is invalid */
        else
        {
            return 5;
        }
    }

    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = pcf8591(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        pcf8591_interface_debug_print("pcf8591: run failed.\n");
    }
    else if (res == 5)
    {
        pcf8591_interface_debug_print("pcf8591: param is invalid.\n");
    }
    else
    {
        pcf8591_interface_debug_print("pcf8591: unknow status code.\n");
    }

    return 0;
}