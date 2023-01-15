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
 * @file      driver_pcf8591_read_write_test.c
 * @brief     driver pcf8591 read write test source file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-02-18
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/18  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/10/17  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */
 
#include "driver_pcf8591_read_write_test.h"
#include <stdlib.h>

static pcf8591_handle_t gs_handle;        /**< pcf8591 handle */

/**
 * @brief     read write test
 * @param[in] addr is the iic device address
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t pcf8591_read_write_test(pcf8591_address_t addr, uint32_t times)
{
    uint8_t res;
    uint8_t reg;
    uint32_t i, j;
    int16_t raws[4];
    float adcs[4];
    int16_t raw;
    float adc;
    uint8_t len;
    pcf8591_info_t info;
    
    /* link functions */
    DRIVER_PCF8591_LINK_INIT(&gs_handle, pcf8591_handle_t);
    DRIVER_PCF8591_LINK_IIC_INIT(&gs_handle, pcf8591_interface_iic_init);
    DRIVER_PCF8591_LINK_IIC_DEINIT(&gs_handle, pcf8591_interface_iic_deinit);
    DRIVER_PCF8591_LINK_IIC_READ_COMMAND(&gs_handle, pcf8591_interface_iic_read_cmd);
    DRIVER_PCF8591_LINK_IIC_WRITE_COMMAND(&gs_handle, pcf8591_interface_iic_write_cmd);
    DRIVER_PCF8591_LINK_DELAY_MS(&gs_handle, pcf8591_interface_delay_ms);
    DRIVER_PCF8591_LINK_DEBUG_PRINT(&gs_handle, pcf8591_interface_debug_print);
    
    /* pcf8591 info */
    res = pcf8591_info(&info);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        pcf8591_interface_debug_print("pcf8591: chip is %s.\n", info.chip_name);
        pcf8591_interface_debug_print("pcf8591: manufacturer is %s.\n", info.manufacturer_name);
        pcf8591_interface_debug_print("pcf8591: interface is %s.\n", info.interface);
        pcf8591_interface_debug_print("pcf8591: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        pcf8591_interface_debug_print("pcf8591: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        pcf8591_interface_debug_print("pcf8591: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        pcf8591_interface_debug_print("pcf8591: max current is %0.2fmA.\n", info.max_current_ma);
        pcf8591_interface_debug_print("pcf8591: max temperature is %0.1fC.\n", info.temperature_max);
        pcf8591_interface_debug_print("pcf8591: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* set addr pin */
    res = pcf8591_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set addr pin failed.\n");
       
        return 1;
    }
    
    /* pcf8591 init */
    res = pcf8591_init(&gs_handle);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: init failed.\n");
       
        return 1;
    }
    
    /* start read test */
    pcf8591_interface_debug_print("pcf8591: start read write test.\n");
    
    /* enable auto increment */
    res = pcf8591_set_auto_increment(&gs_handle, PCF8591_BOOL_TRUE);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set auto increment failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default reference voltage */
    res = pcf8591_set_reference_voltage(&gs_handle, 3.3f);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set reference voltage failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    
    /* mode test */
    pcf8591_interface_debug_print("pcf8591: mode test.\n");
    
    /* set mode AIN0123_GND */
    pcf8591_interface_debug_print("pcf8591: set mode AIN0123_GND.\n");
    res = pcf8591_set_mode(&gs_handle, PCF8591_MODE_AIN0123_GND);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    pcf8591_interface_delay_ms(1000);
    for (i=0; i<times; i++)
    {
        len = 4;
    
        /* read data */
        res = pcf8591_multiple_read(&gs_handle, (int16_t *)raws, (float *)adcs, (uint8_t *)&len);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: multiple read failed.\n");
            (void)pcf8591_deinit(&gs_handle);
            
            return 1;
        }
        for (j=0; j<len; j++)
        {
            pcf8591_interface_debug_print("pcf8591: raw is %d.\n", raws[j]);
            pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adcs[j]);
        }
        pcf8591_interface_delay_ms(1000);
    }

    /* set mode AIN012_AIN3 */
    pcf8591_interface_debug_print("pcf8591: set mode AIN012_AIN3.\n");
    res = pcf8591_set_mode(&gs_handle, PCF8591_MODE_AIN012_AIN3);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    pcf8591_interface_delay_ms(1000);
    for (i=0; i<times; i++)
    {
        len = 4;

        /* read data */
        res = pcf8591_multiple_read(&gs_handle, (int16_t *)raws, (float *)adcs, (uint8_t *)&len);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: multiple read failed.\n");
            (void)pcf8591_deinit(&gs_handle);
            
            return 1;
        }
        for (j=0; j<len; j++)
        {
            pcf8591_interface_debug_print("pcf8591: raw is %d.\n", raws[j]);
            pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adcs[j]);
        }
        pcf8591_interface_delay_ms(1000);
    }

    /* set mode AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN */
    pcf8591_interface_debug_print("pcf8591: set mode AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN.\n");
    res = pcf8591_set_mode(&gs_handle, PCF8591_MODE_AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    pcf8591_interface_delay_ms(1000);
    for (i=0; i<times; i++)
    {
        len = 4;

        /* read data */
        res = pcf8591_multiple_read(&gs_handle, (int16_t *)raws, (float *)adcs, (uint8_t *)&len);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: multiple read failed.\n");
            (void)pcf8591_deinit(&gs_handle);
            
            return 1;
        }
        for (j=0; j<len; j++)
        {
            pcf8591_interface_debug_print("pcf8591: raw is %d.\n", raws[j]);
            pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adcs[j]);
        }
        pcf8591_interface_delay_ms(1000);
    }

    /* set mode AIN0_AIN1_AND_ANI2_AIN3 */
    pcf8591_interface_debug_print("pcf8591: set mode AIN0_AIN1_AND_ANI2_AIN3.\n");
    res = pcf8591_set_mode(&gs_handle, PCF8591_MODE_AIN0_AIN1_AND_ANI2_AIN3);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    pcf8591_interface_delay_ms(1000);
    for (i=0; i<times; i++)
    {
        len = 4;

        /* read data */
        res = pcf8591_multiple_read(&gs_handle, (int16_t *)raws, (float *)adcs, (uint8_t *)&len);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: multiple read failed.\n");
            (void)pcf8591_deinit(&gs_handle);
            
            return 1;
        }
        for (j=0; j<len; j++)
        {
            pcf8591_interface_debug_print("pcf8591: raw is %d.\n", raws[j]);
            pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adcs[j]);
        }
        pcf8591_interface_delay_ms(1000);
    }

    /* channel test */
    pcf8591_interface_debug_print("pcf8591: channel test.\n");

    /* disable auto increment */
    res = pcf8591_set_auto_increment(&gs_handle, PCF8591_BOOL_FALSE);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set auto increment failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }

    /* set mode AIN0123_GND */
    res = pcf8591_set_mode(&gs_handle, PCF8591_MODE_AIN0123_GND);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }

    /* set channel 0 */
    pcf8591_interface_debug_print("pcf8591: set channel 0.\n");
    res = pcf8591_set_channel(&gs_handle, PCF8591_CHANNEL_0);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    pcf8591_interface_delay_ms(1000);
    for (i=0; i<times; i++)
    {
        /* read data */
        res = pcf8591_read(&gs_handle, (int16_t *)&raw, (float *)&adc);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: read failed.\n");
            (void)pcf8591_deinit(&gs_handle);
            
            return 1;
        }
        pcf8591_interface_debug_print("pcf8591: raw is %d.\n", raw);
        pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adc);
        pcf8591_interface_delay_ms(1000);
    }

    /* set channel 1 */
    pcf8591_interface_debug_print("pcf8591: set channel 1.\n");
    res = pcf8591_set_channel(&gs_handle, PCF8591_CHANNEL_1);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    pcf8591_interface_delay_ms(1000);
    for (i=0; i<times; i++)
    {
        /* read data */
        res = pcf8591_read(&gs_handle, (int16_t *)&raw, (float *)&adc);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: read failed.\n");
            (void)pcf8591_deinit(&gs_handle);
            
            return 1;
        }
        pcf8591_interface_debug_print("pcf8591: raw is %d.\n", raw);
        pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adc);
        pcf8591_interface_delay_ms(1000);
    }

    /* set channel 2 */
    pcf8591_interface_debug_print("pcf8591: set channel 2.\n");
    res = pcf8591_set_channel(&gs_handle, PCF8591_CHANNEL_2);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    pcf8591_interface_delay_ms(1000);
    for (i=0; i<times; i++)
    {
        /* read data */
        res = pcf8591_read(&gs_handle, (int16_t *)&raw, (float *)&adc);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: read failed.\n");
            (void)pcf8591_deinit(&gs_handle);
            
            return 1;
        }
        pcf8591_interface_debug_print("pcf8591: raw is %d.\n", raw);
        pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adc);
        pcf8591_interface_delay_ms(1000);
    }

    /* set channel 3 */
    pcf8591_interface_debug_print("pcf8591: set channel 3.\n");
    res = pcf8591_set_channel(&gs_handle, PCF8591_CHANNEL_3);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    
    for (i=0; i<times; i++)
    {
        /* read data */
        res = pcf8591_read(&gs_handle, (int16_t *)&raw, (float *)&adc);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: read failed.\n");
            (void)pcf8591_deinit(&gs_handle);
            
            return 1;
        }
        pcf8591_interface_debug_print("pcf8591: raw is %d.\n", raw);
        pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adc);
        pcf8591_interface_delay_ms(1000);
    }

    /* write test */
    pcf8591_interface_debug_print("pcf8591: write test.\n"); 
    for (i=0; i<times; i++)
    {
        adc = (float)(rand() % 3300) / 1000.0f;
        res = pcf8591_dac_convert_to_register(&gs_handle, adc, (uint8_t *)&reg);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: dac convert to register failed.\n");
            
            return 1;
        }
        res = pcf8591_write(&gs_handle, reg);
        if (res != 0)
        {
            pcf8591_interface_debug_print("pcf8591: write failed.\n");
            
            return 1;
        }
        pcf8591_interface_debug_print("pcf8591: adc is %0.3f.\n", adc);
        pcf8591_interface_debug_print("pcf8591: reg is 0x%02X.\n", reg);
        pcf8591_interface_delay_ms(1000);
    }

    /* finish read test */
    pcf8591_interface_debug_print("pcf8591: finish read test.\n");  
    (void)pcf8591_deinit(&gs_handle);
    
    return 0;
}
