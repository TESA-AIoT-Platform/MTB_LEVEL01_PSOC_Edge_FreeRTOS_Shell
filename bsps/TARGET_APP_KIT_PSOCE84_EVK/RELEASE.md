# KIT_PSOCE84_EVK BSP Release Notes


NOTE: BSPs are versioned by family. This means that version 1.2.0 of any BSP in a family (eg: XMC™ ) will have the same software maturity level. However, not all updates are necessarily applicable for each BSP in the family so not all version numbers will exist for each board. Additionally, new BSPs may not start at version 1.0.0. In the event of adding a common feature across all BSPs, the libraries are assigned the same version number. For example if BSP_A is at v1.3.0 and BSP_B is at v1.2.0, the event will trigger a version update to v1.4.0 for both BSP_A and BSP_B. This allows the common feature to be tracked in a consistent way.

### What's Included?
The KIT_PSOCE84_EVK library includes the following:
* BSP specific makefile to configure the build process for the board
* cybsp.c/h files to initialize the board and any system peripherals
* cybsp_types.h file describing basic board setup
* CM33 Linker script & startup code for GCC and ARM toolchains
* CM55 Linker script & startup code for GCC and ARM toolchains
* Configurator design files (and generated code) to setup board specific peripherals
* .lib file references for all dependent libraries
* API documentation

### What Changed?
#### v0.8.0
* Added bt-fw-ifx-cyw55500a1 as dependency for KIT_PSOCE84_EVK BSP and updated the Bluetooth firmware download baud rate to 3 Mbps
* Support for ModusToolbox&trade; 3.3, memory configuration personality
* Updated bsp dependencies: recipe-make-cat1d v1.0.3, core-lib v1.4.3, mtb-pdl-cat1 v3.11.102
* Renamed DEVICE_MODE to VCORE_ATTRS in bsp.mk file
#### v0.7.0
* Removed RAM linkers 
* KIT_PSOCE84_EVK: CYW55513IUBG A1 silicon support in the BSP 
* KIT_PSOCE84_EVK: BSP dependencies update
#### v0.6.0
* ECO (17.2032 MHz) as source for DPLL LP (DPLL_LP0, DPLL_LP1) and IHO (50 MHz) for DPLL_HP
* Reserved DPLL_LP0 as source for SMIF0 (CLK_HF3) with default 200 MHz frequency
* Reserved DPLL_LP1 (65.536 MHz) as source for CLK_HF7 and divider set to 4 to generate CLK_HF7 = 16.384 MHz
* Used DPLL_HP as source for CLK_HF0 (CM33 = 200 MHz), CLK_HF1 (CM55 = 400 MHz)
* Enabled EXT_CLK (24 MHz) on P7_4 as input to CLK_HF12 (GFXSS)
* ECO -> DPLL_LP0 (200 MHz) -> CLK_HF8 (50 MHz for USB)
* Added aliases for TRACE, USB_HOST_EN, USB_DEVICE_DET, SD_CARD_DET, EXT_CLK, BL_PWM_DISP, DISP_RST, DISP_TP_INT, DISP_TP_RST pins
* Updated bsp.mk file to support ARM compiler
* Replaced CYW955513WLIPA with CYW55513IUBG as component for connectivity chip
* Updated Deep Sleep Latency = 20 ms
* Updated VDDD, VDDA, VDDIO0 and VDDIO1 values from 3.3 mV to 1.8 mV
* Updated bsp dependencies: recipe-make-cat1d, mtb-pdl-cat1 and mtb-hal-cat1
#### v0.5.2
* System Idle Power Mode = System Deep Sleep
* Removed prebuilt binaries for CM33 secure application
* Arm compiler support
#### v0.5.1
* CLK_HF3 = 200 MHz
* System Idle Power Mode = CPU Sleep
#### v0.5.0
* Initial pre-production release

### Supported Software and Tools
This version of the KIT_PSOCE84_EVK BSP was validated for compatibility with the following Software and Tools:

| Software and Tools                        | Version |
| :---                                      | :----:  |
| ModusToolbox™ Software Environment        | 3.3.0   |
| GCC Compiler                              | 12.2.1  |
| ARM Compiler                              | 6.16    |

Minimum required ModusToolbox™ Software Environment: v3.3.0

### More information
* [KIT_PSOCE84_EVK BSP API Reference Manual][api]
* [KIT_PSOCE84_EVK Documentation](https://www.infineon.com/cms/en/product/evaluation-boards/placeholder/)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Infineon GitHub](https://github.com/infineon)
* [ModusToolbox™](https://www.cypress.com/products/modustoolbox-software-environment)

[api]: https://infineon.github.io/TARGET_KIT_PSOCE84_EVK/html/modules.html

---
© Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation, 2019-2023.