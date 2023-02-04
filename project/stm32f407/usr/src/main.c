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
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     pcf8591 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t pcf8591(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"channel", required_argument, NULL, 2},
        {"dac", required_argument, NULL, 3},
        {"mode", required_argument, NULL, 4},
        {"times", required_argument, NULL, 5},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    pcf8591_address_t addr = PCF8591_ADDRESS_A000;
    pcf8591_channel_t channel = PCF8591_CHANNEL_0;
    pcf8591_mode_t mode = PCF8591_MODE_AIN0123_GND;
    float dac = 0.0f;
    uint8_t dac_flag = 0;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("0", optarg) == 0)
                {
                    addr = PCF8591_ADDRESS_A000;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = PCF8591_ADDRESS_A001;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    addr = PCF8591_ADDRESS_A010;
                }
                else if (strcmp("3", optarg) == 0)
                {
                    addr = PCF8591_ADDRESS_A011;
                }
                else if (strcmp("4", optarg) == 0)
                {
                    addr = PCF8591_ADDRESS_A100;
                }
                else if (strcmp("5", optarg) == 0)
                {
                    addr = PCF8591_ADDRESS_A101;
                }
                else if (strcmp("6", optarg) == 0)
                {
                    addr = PCF8591_ADDRESS_A110;
                }
                else if (strcmp("7", optarg) == 0)
                {
                    addr = PCF8591_ADDRESS_A111;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* channel */
            case 2 :
            {
                /* set the channel */
                if (strcmp("0", optarg) == 0)
                {
                    channel = PCF8591_CHANNEL_0;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    channel = PCF8591_CHANNEL_1;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    channel = PCF8591_CHANNEL_2;
                }
                else if (strcmp("3", optarg) == 0)
                {
                    channel = PCF8591_CHANNEL_3;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* dac */
            case 3 :
            {
                /* set the dac */
                dac = atof(optarg);
                dac_flag = 1;

                break;
            }
             
            /* mode */
            case 4 :
            {
                /* set the mode */
                if (strcmp("AIN0123_GND", optarg) == 0)
                {
                    mode = PCF8591_MODE_AIN0123_GND;
                }
                else if (strcmp("AIN012_AIN3", optarg) == 0)
                {
                    mode = PCF8591_MODE_AIN012_AIN3;
                }
                else if (strcmp("AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3", optarg) == 0)
                {
                    mode = PCF8591_MODE_AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3;
                }
                else if (strcmp("AIN1_AND_ANI2_AIN3", optarg) == 0)
                {
                    mode = PCF8591_MODE_AIN0_AIN1_AND_ANI2_AIN3;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 5 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (pcf8591_register_test(addr) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_readwrite", type) == 0)
    {
        /* run readwrite test */
        if (pcf8591_read_write_test(addr, times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_basic-input", type) == 0)
    {
        uint8_t res;
        int16_t raw;
        float adc;
        uint32_t i;
        
        /* basic init */
        res = pcf8591_basic_init(addr, mode);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: init failed.\n");
            
            return 1;
        }
        
        /* set the channel */
        res = pcf8591_basic_set_channel(channel);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
            (void)pcf8591_basic_deinit();
            
            return 1;
        }
        
        /* read prev data */
        res = pcf8591_basic_read((int16_t *)&raw, (float *)&adc);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: read failed.\n");
            (void)pcf8591_basic_deinit();
            
            return 1;
        }
        
        /* delay 1000ms */
        pcf8591_interface_delay_ms(1000);
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* read data */
            res = pcf8591_basic_read((int16_t *)&raw, (float *)&adc);
            if (res != 0)
            {
                pcf8591_interface_debug_print("pcf8591: read failed.\n");
                (void)pcf8591_basic_deinit();
                
                return 1;
            }
            
            /* output */
            pcf8591_interface_debug_print("pcf8591: %d/%d.\n", i + 1, times);
            pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adc);
            
            /* delay 1000ms */
            pcf8591_interface_delay_ms(1000);
        }
        
        /* basic deinit */
        (void)pcf8591_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_basic-output", type) == 0)
    {
        uint8_t res;
        
        /* check the dac */
        if (dac_flag != 1)
        {
            return 5;
        }
        
        /* basic init */
        res = pcf8591_basic_init(addr, mode);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: init failed.\n");
            
            return 1;
        }
        
        /* write dac */
        res = pcf8591_basic_write(dac);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: write failed.\n");
            (void)pcf8591_basic_deinit();
            
            return 1;
        }
        
        /* output */
        pcf8591_interface_debug_print("pcf8591: write %0.3f.\n", dac);
        
        /* basic deinit */
        (void)pcf8591_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_increment-input", type) == 0)
    {
        uint8_t res;
        uint8_t len;
        int16_t raws[4];
        float adcs[4];
        uint32_t i;
        uint32_t j;
        
        /* increment init */
        res = pcf8591_increment_init(addr, mode);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: init failed.\n");
            
            return 1;
        }
        
        /* read prev data */
        len = 4;
        res = pcf8591_increment_read((int16_t *)raws, (float *)adcs, (uint8_t *)&len);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: increment read failed.\n");
            (void)pcf8591_increment_deinit();
            
            return 1;
        }
        
        /* delay 1000ms */
        pcf8591_interface_delay_ms(1000);
        
        /* loop */
        for (i = 0; i < times; i++)
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
            
            /* output */
            pcf8591_interface_debug_print("pcf8591: %d/%d.\n", i + 1, times);
            for (j = 0; j < len; j++)
            {
                pcf8591_interface_debug_print("pcf8591: raw is %d.\n", raws[j]);
                pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adcs[j]);
            }
            
            /* delay 1000ms */
            pcf8591_interface_delay_ms(1000);
        }
        
        /* increment deinit */
        (void)pcf8591_increment_deinit();
        
        return 0;
    }
    else if (strcmp("e_increment-output", type) == 0)
    {
        uint8_t res;
        
        /* check the dac */
        if (dac_flag != 1)
        {
            return 5;
        }
        
        /* increment init */
        res = pcf8591_increment_init(addr, mode);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: init failed.\n");
            
            return 1;
        }
        
        /* write dac */
        res = pcf8591_increment_write(dac);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: write failed.\n");
            (void)pcf8591_increment_deinit();
            
            return 1;
        }
        
        /* output */
        pcf8591_interface_debug_print("pcf8591: write %0.3f.\n", dac);
        
        /* increment deinit */
        (void)pcf8591_increment_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        pcf8591_interface_debug_print("Usage:\n");
        pcf8591_interface_debug_print("  pcf8591 (-i | --information)\n");
        pcf8591_interface_debug_print("  pcf8591 (-h | --help)\n");
        pcf8591_interface_debug_print("  pcf8591 (-p | --port)\n");
        pcf8591_interface_debug_print("  pcf8591 (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pcf8591_interface_debug_print("  pcf8591 (-t readwrite | --test=readwrite) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]\n");
        pcf8591_interface_debug_print("  pcf8591 (-e basic-input | --example=basic-input) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]\n");
        pcf8591_interface_debug_print("          [--mode=<AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3>]\n");
        pcf8591_interface_debug_print("          [--channel=<0 | 1 | 2 | 3>]\n");
        pcf8591_interface_debug_print("  pcf8591 (-e basic-output | --example=basic-output) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pcf8591_interface_debug_print("          --dac=<voltage>\n");
        pcf8591_interface_debug_print("  pcf8591 (-e increment-input | --example=increment-input) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]\n");
        pcf8591_interface_debug_print("          [--mode=<AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3>]\n");
        pcf8591_interface_debug_print("  pcf8591 (-e increment-output | --example=increment-output) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pcf8591_interface_debug_print("          --dac=<voltage>\n");
        pcf8591_interface_debug_print("\n");
        pcf8591_interface_debug_print("Options:\n");
        pcf8591_interface_debug_print("      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>\n");
        pcf8591_interface_debug_print("                                   Set the addr pin.([default: 0])\n");
        pcf8591_interface_debug_print("      --channel=<0 | 1 | 2 | 3>    Set the used channel.([default: 0])\n");
        pcf8591_interface_debug_print("      --dac=<voltage>              Set the dac value in voltage.\n");
        pcf8591_interface_debug_print("  -e <basic-input | basic-output | increment-input | increment-output>, --example=<basic-input\n");
        pcf8591_interface_debug_print("     | basic-output | increment-input | increment-output>\n");
        pcf8591_interface_debug_print("                                   Run the driver example.\n");
        pcf8591_interface_debug_print("  -h, --help                       Show the help.\n");
        pcf8591_interface_debug_print("  -i, --information                Show the chip information.\n");
        pcf8591_interface_debug_print("      --mode=<AIN0123_GND | AIN012_AIN3 | AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 | AIN1_AND_ANI2_AIN3>\n");
        pcf8591_interface_debug_print("                                   Set the chip mode.([default: AIN0123_GND])\n");
        pcf8591_interface_debug_print("  -p, --port                       Display the pin connections of the current board.\n");
        pcf8591_interface_debug_print("  -t <reg | readwrite>, --test=<reg | readwrite>\n");
        pcf8591_interface_debug_print("                                   Run the driver test.\n");
        pcf8591_interface_debug_print("      --times=<num>                Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        pcf8591_info_t info;
        
        /* print pcf8591 info */
        pcf8591_info(&info);
        pcf8591_interface_debug_print("pcf8591: chip is %s.\n", info.chip_name);
        pcf8591_interface_debug_print("pcf8591: manufacturer is %s.\n", info.manufacturer_name);
        pcf8591_interface_debug_print("pcf8591: interface is %s.\n", info.interface);
        pcf8591_interface_debug_print("pcf8591: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        pcf8591_interface_debug_print("pcf8591: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        pcf8591_interface_debug_print("pcf8591: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        pcf8591_interface_debug_print("pcf8591: max current is %0.2fmA.\n", info.max_current_ma);
        pcf8591_interface_debug_print("pcf8591: max temperature is %0.1fC.\n", info.temperature_max);
        pcf8591_interface_debug_print("pcf8591: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        pcf8591_interface_debug_print("pcf8591: SCL connected to GPIOB PIN8.\n");
        pcf8591_interface_debug_print("pcf8591: SDA connected to GPIOB PIN9.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register pcf8591 function */
    shell_init();
    shell_register("pcf8591", pcf8591);
    uart_print("pcf8591: welcome to libdriver pcf8591.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("pcf8591: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("pcf8591: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("pcf8591: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("pcf8591: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("pcf8591: param is invalid.\n");
            }
            else
            {
                uart_print("pcf8591: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
