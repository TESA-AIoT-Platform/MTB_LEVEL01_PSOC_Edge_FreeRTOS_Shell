/*******************************************************************************
 * File Name: cycfg_pins.h
 *
 * Description:
 * Pin configuration
 * This file was automatically generated and should not be modified.
 * Configurator Backend 3.30.0
 * device-db 4.5.10.7101
 * mtb-pdl-cat1 3.11.102.37230
 *
 *******************************************************************************
 * Copyright 2025 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#if !defined(CYCFG_PINS_H)
#define CYCFG_PINS_H

#include "cycfg_notices.h"
#include "cy_gpio.h"
#include "cycfg_routing.h"

#if defined (CY_USING_HAL)
#include "cyhal_hwmgr.h"
#endif /* defined (CY_USING_HAL) */

#if defined (CY_USING_HAL_LITE)
#include "cyhal_hw_types.h"
#endif /* defined (CY_USING_HAL_LITE) */

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_OSPI_RAM_SS (P0_1)
#define CYBSP_BT_UART_RX (P10_0)
#define CYBSP_BT_UART_TX (P10_1)
#define CYBSP_BT_UART_CTS (P10_2)
#define CYBSP_BT_UART_RTS (P10_3)
#define CYBSP_BT_HOST_WAKE (P10_4)
#define CYBSP_BT_DEVICE_WAKE (P10_6)
#define CYBSP_BT_POWER (P11_0)
#define CYBSP_WIFI_HOST_WAKE (P11_4)
#define CYBSP_WIFI_WL_REG_ON (P11_6)
#define CYBSP_WIFI_SDIO_CLK (P12_0)
#define CYBSP_WIFI_SDIO_D0 (P12_1)
#define CYBSP_WIFI_SDIO_D1 (P12_2)
#define CYBSP_WIFI_SDIO_D2 (P12_4)
#define CYBSP_WIFI_SDIO_D3 (P12_5)
#define CYBSP_SPI_CLK (P16_0)
#define CYBSP_SPI_MOSI (P16_1)
#define CYBSP_SPI_MISO (P16_2)
#define CYBSP_SPI_CS (P16_3)
#define CYBSP_USER_LED3 (P16_5)
#define CYBSP_LED_BLUE CYBSP_USER_LED3
#define CYBSP_USER_LED2 (P16_6)
#define CYBSP_LED_GREEN CYBSP_USER_LED2
#define CYBSP_USER_LED1 (P16_7)
#define CYBSP_USER_LED CYBSP_USER_LED1
#define CYBSP_LED_RED CYBSP_USER_LED1
#define CYBSP_DISP_TP_INT (P17_2)
#define CYBSP_DISP_TP_RST (P17_3)
#define CYBSP_USB_DEVICE_VBUS_DETECT (P17_4)
#define CYBSP_USB_HOST_ENABLE_POWER (P17_5)
#define CYBSP_SDHC_DETECT (P17_7)
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_WCO_OUT_ENABLED 1U
#define CYBSP_WCO_OUT_PORT GPIO_PRT18
#define CYBSP_WCO_OUT_PORT_NUM 18U
#define CYBSP_WCO_OUT_PIN 0U
#define CYBSP_WCO_OUT_NUM 0U
#define CYBSP_WCO_OUT_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_WCO_OUT_INIT_DRIVESTATE 1
#ifndef ioss_0_port_18_pin_0_HSIOM
    #define ioss_0_port_18_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_WCO_OUT_HSIOM ioss_0_port_18_pin_0_HSIOM
#define CYBSP_WCO_OUT_IRQ ioss_interrupts_gpio_18_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_WCO_OUT_HAL_PORT_PIN P18_0
#define CYBSP_WCO_OUT P18_0
#define CYBSP_WCO_OUT_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_WCO_OUT_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_WCO_OUT_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_WCO_IN_ENABLED 1U
#define CYBSP_WCO_IN_PORT GPIO_PRT18
#define CYBSP_WCO_IN_PORT_NUM 18U
#define CYBSP_WCO_IN_PIN 1U
#define CYBSP_WCO_IN_NUM 1U
#define CYBSP_WCO_IN_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_WCO_IN_INIT_DRIVESTATE 1
#ifndef ioss_0_port_18_pin_1_HSIOM
    #define ioss_0_port_18_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_WCO_IN_HSIOM ioss_0_port_18_pin_1_HSIOM
#define CYBSP_WCO_IN_IRQ ioss_interrupts_gpio_18_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_WCO_IN_HAL_PORT_PIN P18_1
#define CYBSP_WCO_IN P18_1
#define CYBSP_WCO_IN_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_WCO_IN_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_WCO_IN_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define ioss_0_port_19_pin_0_ENABLED 1U
#define ioss_0_port_19_pin_0_PORT GPIO_PRT19
#define ioss_0_port_19_pin_0_PORT_NUM 19U
#define ioss_0_port_19_pin_0_PIN 0U
#define ioss_0_port_19_pin_0_NUM 0U
#define ioss_0_port_19_pin_0_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_19_pin_0_INIT_DRIVESTATE 1
#ifndef ioss_0_port_19_pin_0_HSIOM
    #define ioss_0_port_19_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_19_pin_0_IRQ ioss_interrupts_gpio_19_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define ioss_0_port_19_pin_0_HAL_PORT_PIN P19_0
#define ioss_0_port_19_pin_0 P19_0
#define ioss_0_port_19_pin_0_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define ioss_0_port_19_pin_0_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define ioss_0_port_19_pin_0_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define ioss_0_port_19_pin_1_ENABLED 1U
#define ioss_0_port_19_pin_1_PORT GPIO_PRT19
#define ioss_0_port_19_pin_1_PORT_NUM 19U
#define ioss_0_port_19_pin_1_PIN 1U
#define ioss_0_port_19_pin_1_NUM 1U
#define ioss_0_port_19_pin_1_DRIVEMODE CY_GPIO_DM_ANALOG
#define ioss_0_port_19_pin_1_INIT_DRIVESTATE 1
#ifndef ioss_0_port_19_pin_1_HSIOM
    #define ioss_0_port_19_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_19_pin_1_IRQ ioss_interrupts_gpio_19_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define ioss_0_port_19_pin_1_HAL_PORT_PIN P19_1
#define ioss_0_port_19_pin_1 P19_1
#define ioss_0_port_19_pin_1_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define ioss_0_port_19_pin_1_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define ioss_0_port_19_pin_1_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#define CYBSP_OSPI_D0 (P1_0)
#define CYBSP_QSPI_D0 CYBSP_OSPI_D0
#define CYBSP_OSPI_D1 (P1_1)
#define CYBSP_QSPI_D1 CYBSP_OSPI_D1
#define CYBSP_OSPI_D2 (P1_2)
#define CYBSP_QSPI_D2 CYBSP_OSPI_D2
#define CYBSP_OSPI_D3 (P1_3)
#define CYBSP_QSPI_D3 CYBSP_OSPI_D3
#define CYBSP_OSPI_D4 (P1_4)
#define CYBSP_OSPI_D5 (P1_5)
#define CYBSP_OSPI_D6 (P1_6)
#define CYBSP_OSPI_D7 (P1_7)
#define CYBSP_TRACE_CLK (P20_0)
#define CYBSP_TRACE_DATA3 (P20_1)
#define CYBSP_TRACE_DATA2 (P20_2)
#define CYBSP_TRACE_DATA1 (P20_3)
#define CYBSP_TRACE_DATA0 (P20_4)
#define CYBSP_DISP_BACKLIGHT_PWM (P20_6)
#define CYBSP_DISP_RST (P20_7)
#define CYBSP_WIFI_SDIO_CMD (P21_0)
#define CYBSP_QSPI_SS (P2_0)
#define CYBSP_I3C_SCL (P3_0)
#define CYBSP_I3C_SDA (P3_1)
#define CYBSP_OSPI_RAM_D0 (P4_0)
#define CYBSP_OSPI_RAM_D1 (P4_1)
#define CYBSP_OSPI_RAM_D2 (P4_2)
#define CYBSP_OSPI_RAM_D3 (P4_3)
#define CYBSP_OSPI_RAM_D4 (P4_4)
#define CYBSP_OSPI_RAM_D5 (P4_5)
#define CYBSP_OSPI_RAM_D6 (P4_6)
#define CYBSP_OSPI_RAM_D7 (P4_7)
#define CYBSP_OSPI_SS (P5_0)
#define CYBSP_SWO (P6_0)
#define CYBSP_SWDIO (P6_2)
#define CYBSP_SWDCK (P6_3)
#define CYBSP_DEBUG_UART_CTS (P6_4)
#define CYBSP_DEBUG_UART_RX (P6_5)
#define CYBSP_DEBUG_UART_RTS (P6_6)
#define CYBSP_DEBUG_UART_TX (P6_7)
#define CYBSP_SDHC_CMD (P7_0)
#define CYBSP_SDHC_CLK (P7_1)
#define CYBSP_SDHC_IO0 (P7_3)
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define CYBSP_EXT_CLK_ENABLED 1U
#define CYBSP_EXT_CLK_PORT GPIO_PRT7
#define CYBSP_EXT_CLK_PORT_NUM 7U
#define CYBSP_EXT_CLK_PIN 4U
#define CYBSP_EXT_CLK_NUM 4U
#define CYBSP_EXT_CLK_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_EXT_CLK_INIT_DRIVESTATE 1
#ifndef ioss_0_port_7_pin_4_HSIOM
    #define ioss_0_port_7_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_EXT_CLK_HSIOM ioss_0_port_7_pin_4_HSIOM
#define CYBSP_EXT_CLK_IRQ ioss_interrupts_gpio_7_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_EXT_CLK_HAL_PORT_PIN P7_4
#define CYBSP_EXT_CLK P7_4
#define CYBSP_EXT_CLK_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_EXT_CLK_HAL_DIR CYHAL_GPIO_DIR_INPUT 
#define CYBSP_EXT_CLK_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#define CYBSP_SDHC_IO1 (P7_5)
#define CYBSP_SDHC_IO2 (P7_6)
#define CYBSP_SDHC_IO3 (P7_7)
#define CYBSP_I2C_SCL (P8_0)
#define CYBSP_I2C_SDA (P8_1)
#define CYBSP_SW2 (P8_3)
#define CYBSP_USER_BTN1 CYBSP_SW2
#define CYBSP_USER_BTN CYBSP_SW2
#define CYBSP_SW4 (P8_7)
#define CYBSP_USER_BTN2 CYBSP_SW4
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_WCO_OUT_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_WCO_OUT_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_WCO_IN_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_WCO_IN_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t ioss_0_port_19_pin_0_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t ioss_0_port_19_pin_0_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t ioss_0_port_19_pin_1_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t ioss_0_port_19_pin_1_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_EXT_CLK_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_EXT_CLK_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

void init_cycfg_pins(void);
void reserve_cycfg_pins(void);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_PINS_H */
