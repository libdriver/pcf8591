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
 * @file      driver_pcf8591_basic.h
 * @brief     driver pcf8591 basic include file
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

#ifndef DRIVER_PCF8591_BASIC_H
#define DRIVER_PCF8591_BASIC_H

#include "driver_pcf8591_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup pcf8591_example_driver pcf8591 example driver function
 * @brief    pcf8591 example driver modules
 * @ingroup  pcf8591_driver
 * @{
 */

/**
 * @brief pcf8591 basic example default definition
 */
#define PCF8591_BASIC_DEFAULT_REFERENCE_VOLTAGE        3.3f        /**< set 3.3V reference voltage */

/**
 * @brief     basic example init
 * @param[in] addr is the iic device address
 * @param[in] mode is the adc mode
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t pcf8591_basic_init(pcf8591_address_t addr, pcf8591_mode_t mode);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t pcf8591_basic_deinit(void);

/**
 * @brief     basic example set the channel
 * @param[in] channel is the adc channel
 * @return    status code
 *            - 0 success
 *            - 1 set channel failed
 * @note      none
 */
uint8_t pcf8591_basic_set_channel(pcf8591_channel_t channel);

/**
 * @brief      basic example read the adc
 * @param[out] *raw points to a raw adc buffer
 * @param[out] *adc points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t pcf8591_basic_read(int16_t *raw, float *adc);

/**
 * @brief     basic example write the dac
 * @param[in] dac is a converted dac value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t pcf8591_basic_write(float adc);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
