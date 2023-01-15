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
 * @file      driver_pcf8591_register_test.c
 * @brief     driver pcf8591 register test source file
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

#include "driver_pcf8591_register_test.h"
#include <stdlib.h>

static pcf8591_handle_t gs_handle;        /**< pcf8591 handle */

/**
 * @brief     register test
 * @param[in] addr is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t pcf8591_register_test(pcf8591_address_t addr)
{
    uint8_t res;
    uint8_t reg;
    float ref_voltage;
    float ref_voltage_check;
    pcf8591_info_t info;
    pcf8591_address_t address_pin;
    pcf8591_channel_t channel;
    pcf8591_mode_t mode;
    pcf8591_bool_t enable;
    
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
    
    /* start register test */
    pcf8591_interface_debug_print("pcf8591: start register test.\n");
    pcf8591_interface_debug_print("pcf8591: pcf8591_set_addr_pin/pcf8591_get_addr_pin test.\n");
    
    /* set addr pin a000 */
    res = pcf8591_set_addr_pin(&gs_handle, PCF8591_ADDRESS_A000);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set addr pin a000.\n");
    res = pcf8591_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check addr pin %s.\n", (PCF8591_ADDRESS_A000==address_pin)?"ok":"error");
    
    /* set addr pin a001 */
    res = pcf8591_set_addr_pin(&gs_handle, PCF8591_ADDRESS_A001);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set addr pin a001.\n");
    res = pcf8591_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check addr pin %s.\n", (PCF8591_ADDRESS_A001==address_pin)?"ok":"error");
    
    /* set addr pin a010 */
    res = pcf8591_set_addr_pin(&gs_handle, PCF8591_ADDRESS_A010);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set addr pin a010.\n");
    res = pcf8591_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check addr pin %s.\n", (PCF8591_ADDRESS_A010==address_pin)?"ok":"error");
    
    /* set addr pin a011 */
    res = pcf8591_set_addr_pin(&gs_handle, PCF8591_ADDRESS_A011);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set addr pin a011.\n");
    res = pcf8591_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check addr pin %s.\n", (PCF8591_ADDRESS_A011==address_pin)?"ok":"error");
    
    /* set addr pin a100 */
    res = pcf8591_set_addr_pin(&gs_handle, PCF8591_ADDRESS_A100);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set addr pin a100.\n");
    res = pcf8591_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check addr pin %s.\n", (PCF8591_ADDRESS_A100==address_pin)?"ok":"error");
    
    /* set addr pin a101 */
    res = pcf8591_set_addr_pin(&gs_handle, PCF8591_ADDRESS_A101);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set addr pin a101.\n");
    res = pcf8591_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check addr pin %s.\n", (PCF8591_ADDRESS_A101==address_pin)?"ok":"error");
    
    /* set addr pin a110 */
    res = pcf8591_set_addr_pin(&gs_handle, PCF8591_ADDRESS_A110);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set addr pin a110.\n");
    res = pcf8591_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check addr pin %s.\n", (PCF8591_ADDRESS_A110==address_pin)?"ok":"error");
    
    /* set addr pin a111 */
    res = pcf8591_set_addr_pin(&gs_handle, PCF8591_ADDRESS_A111);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set addr pin a111.\n");
    res = pcf8591_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get addr pin failed.\n");
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check addr pin %s.\n", (PCF8591_ADDRESS_A111==address_pin)?"ok":"error");
    
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
    
    /* pcf8591_set_channel/pcf8591_get_channel test */
    pcf8591_interface_debug_print("pcf8591: pcf8591_set_channel/pcf8591_get_channel test.\n");
    
    /* channel 0 */
    res = pcf8591_set_channel(&gs_handle, PCF8591_CHANNEL_0);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set channel 0.\n");
    res = pcf8591_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check channel %s.\n", (PCF8591_CHANNEL_0==channel)?"ok":"error");
    
    /* channel 1 */
    res = pcf8591_set_channel(&gs_handle, PCF8591_CHANNEL_1);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set channel 1.\n");
    res = pcf8591_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check channel %s.\n", (PCF8591_CHANNEL_1==channel)?"ok":"error");
    
    /* channel 2 */
    res = pcf8591_set_channel(&gs_handle, PCF8591_CHANNEL_2);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set channel 2.\n");
    res = pcf8591_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check channel %s.\n", (PCF8591_CHANNEL_2==channel)?"ok":"error");
    
    /* channel 3 */
    res = pcf8591_set_channel(&gs_handle, PCF8591_CHANNEL_3);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set channel 3.\n");
    res = pcf8591_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check channel %s.\n", (PCF8591_CHANNEL_3==channel)?"ok":"error");
    
    /* channel 1 */
    res = pcf8591_set_channel(&gs_handle, PCF8591_CHANNEL_1);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set channel failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    
    /* pcf8591_set_mode/pcf8591_get_mode test */
    pcf8591_interface_debug_print("pcf8591: pcf8591_set_mode/pcf8591_get_mode test.\n");
    
    /* set mode AIN0123_GND */
    res = pcf8591_set_mode(&gs_handle, PCF8591_MODE_AIN0123_GND);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set mode AIN0123_GND.\n");
    res = pcf8591_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check mode %s.\n", (PCF8591_MODE_AIN0123_GND==mode)?"ok":"error");
    
    /* set mode AIN012_AIN3 */
    res = pcf8591_set_mode(&gs_handle, PCF8591_MODE_AIN012_AIN3);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set mode AIN012_AIN3.\n");
    res = pcf8591_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check mode %s.\n", (PCF8591_MODE_AIN012_AIN3==mode)?"ok":"error");
    
    /* set mode AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3 */
    res = pcf8591_set_mode(&gs_handle, PCF8591_MODE_AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set mode AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3.\n");
    res = pcf8591_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check mode %s.\n", (PCF8591_MODE_AIN0_GND_AND_AIN1_GND_AND_AIN2_AIN3==mode)?"ok":"error");
    
    /* set mode AIN0_AIN1_AND_ANI2_AIN3 */
    res = pcf8591_set_mode(&gs_handle, PCF8591_MODE_AIN0_AIN1_AND_ANI2_AIN3);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: set mode AIN0_AIN1_AND_ANI2_AIN3.\n");
    res = pcf8591_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check mode %s.\n", (PCF8591_MODE_AIN0_AIN1_AND_ANI2_AIN3==mode)?"ok":"error");
    
    /* pcf8591_set_auto_increment/pcf8591_get_auto_increment test */
    pcf8591_interface_debug_print("pcf8591: pcf8591_set_auto_increment/pcf8591_get_auto_increment test.\n");
    
    /* enable */
    res = pcf8591_set_auto_increment(&gs_handle, PCF8591_BOOL_TRUE);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set auto increment failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: enable auto increment.\n");
    res = pcf8591_get_auto_increment(&gs_handle, &enable);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get auto increment failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check auto increment %s.\n", (PCF8591_BOOL_TRUE==enable)?"ok":"error");
    
    /* disable */
    res = pcf8591_set_auto_increment(&gs_handle, PCF8591_BOOL_FALSE);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set auto increment failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: disable auto increment.\n");
    res = pcf8591_get_auto_increment(&gs_handle, &enable);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get auto increment failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check auto increment %s.\n", (PCF8591_BOOL_FALSE==enable)?"ok":"error");
    
    /* pcf8591_set_reference_voltage/pcf8591_get_reference_voltage test */
    pcf8591_interface_debug_print("pcf8591: pcf8591_set_reference_voltage/pcf8591_get_reference_voltage test.\n");
    ref_voltage = (float)(rand() % 200) / 100.0f;
    pcf8591_interface_debug_print("pcf8591: set ref voltage %0.3f.\n", ref_voltage);
    res = pcf8591_set_reference_voltage(&gs_handle, ref_voltage);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set reference voltage failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    res = pcf8591_get_reference_voltage(&gs_handle, (float *)&ref_voltage_check);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: get reference voltage failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check reference voltage %0.3f.\n", ref_voltage_check);
    
    /* pcf8591_dac_convert_to_register test */
    pcf8591_interface_debug_print("pcf8591: pcf8591_dac_convert_to_register test.\n");
    ref_voltage = (float)(rand() % 200) / 100.0f;
    pcf8591_interface_debug_print("pcf8591: set convert voltage %0.3f.\n", ref_voltage);
    res = pcf8591_dac_convert_to_register(&gs_handle, ref_voltage, (uint8_t *)&reg);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: dac convert to register failed.\n");
        (void)pcf8591_deinit(&gs_handle);
       
        return 1;
    }
    pcf8591_interface_debug_print("pcf8591: check register 0x%02X.\n", reg);
    
    /* finish register test */
    pcf8591_interface_debug_print("pcf8591: finish register test.\n");
    (void)pcf8591_deinit(&gs_handle);
    
    return 0;
}
