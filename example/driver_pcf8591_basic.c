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
 * @file      driver_pcf8591_basic.c
 * @brief     driver pcf8591 basic source file
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

#include "driver_pcf8591_basic.h"

static pcf8591_handle_t gs_handle;        /**< pcf8591 handle */

/**
 * @brief     basic example init
 * @param[in] addr is the iic device address
 * @param[in] mode is the adc mode
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t pcf8591_basic_init(pcf8591_address_t addr, pcf8591_mode_t mode)
{
    uint8_t res;

    /* link functions */
    DRIVER_PCF8591_LINK_INIT(&gs_handle, pcf8591_handle_t);
    DRIVER_PCF8591_LINK_IIC_INIT(&gs_handle, pcf8591_interface_iic_init);
    DRIVER_PCF8591_LINK_IIC_DEINIT(&gs_handle, pcf8591_interface_iic_deinit);
    DRIVER_PCF8591_LINK_IIC_READ_COMMAND(&gs_handle, pcf8591_interface_iic_read_cmd);
    DRIVER_PCF8591_LINK_IIC_WRITE_COMMAND(&gs_handle, pcf8591_interface_iic_write_cmd);
    DRIVER_PCF8591_LINK_DELAY_MS(&gs_handle, pcf8591_interface_delay_ms);
    DRIVER_PCF8591_LINK_DEBUG_PRINT(&gs_handle, pcf8591_interface_debug_print);
    
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
    
    /* set mode */
    res = pcf8591_set_mode(&gs_handle, mode);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set mode failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable auto increment */
    res = pcf8591_set_auto_increment(&gs_handle, PCF8591_BOOL_FALSE);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set auto increment failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default reference voltage */
    res = pcf8591_set_reference_voltage(&gs_handle, PCF8591_BASIC_DEFAULT_REFERENCE_VOLTAGE);
    if (res != 0)
    {
        pcf8591_interface_debug_print("pcf8591: set reference voltage failed.\n");
        (void)pcf8591_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t pcf8591_basic_deinit(void)
{
    /* close pcf8591 */
    if (pcf8591_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     basic example set the channel
 * @param[in] channel is the adc channel
 * @return    status code
 *            - 0 success
 *            - 1 set channel failed
 * @note      none
 */
uint8_t pcf8591_basic_set_channel(pcf8591_channel_t channel)
{
    uint8_t res;
    
    /* set channel */
    res = pcf8591_set_channel(&gs_handle, channel);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read the adc
 * @param[out] *raw points to a raw adc buffer
 * @param[out] *adc points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t pcf8591_basic_read(int16_t *raw, float *adc)
{
    /* read data */
    if (pcf8591_read(&gs_handle, raw, adc) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     basic example write the dac
 * @param[in] dac is a converted dac value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t pcf8591_basic_write(float dac)
{
    uint8_t res;
    uint8_t data;
    
    /* convert to register data */
    res = pcf8591_dac_convert_to_register(&gs_handle, dac, (uint8_t *)&data);
    if (res != 0)
    {
        return 1;
    }
    
    /* write dac */
    if (pcf8591_write(&gs_handle, data) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
