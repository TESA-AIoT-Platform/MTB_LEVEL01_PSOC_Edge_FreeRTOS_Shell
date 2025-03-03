# PSOC&trade; Edge MCU: FreeRTOS with TESA Shell template

This is a minimal FreeRTOS-based Shell application template for PSOC&trade; Edge MCU devices. This example uses FreeRTOS to blink two LEDs with different frequencies respectively from the Arm&reg; Cortex&reg; M33 CPU and the Arm&reg; Cortex&reg; M55 CPU. 

This Code Example has a three project structure - CM33 Secure, CM33 Non-Secure, and CM55 projects. All three projects are programmed to the external QSPI flash and executed in XIP mode. Extended Boot launches the CM33 Secure project from a fixed location in the external flash, which then configures the protection settings and launches the CM33 Non-Secure application. Additionally, CM33 Non-Secure application enables CM55 CPU and launches the CM55 application.

## Requirements

- [ModusToolbox&trade; software](https://www.infineon.com/modustoolbox) v3.3 or later (tested with v3.3)
- ModusToolbox&trade; PSOC&trade; E84 Early Access Pack. See [Software setup](#software-setup) for more details.
- Extended Boot v1.1.0.1333 or later. See [Software setup](#software-setup) for more details.
- Board support package (BSP) minimum required version for:
   - KIT_PSOCE84_EVK: v0.8.0
- Programming language: C
- Associated parts: All PSOC&trade; Edge E84 MCU parts

## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; embedded compiler v11.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`
- Arm&reg; Compiler v6.22 (`ARM`)
- IAR C/C++ Compiler v9.50.2 (`IAR`)

## Supported kits (make variable 'TARGET')

- **PSOC&trade; Edge E84 Evaluation Kit** (`KIT_PSOCE84_EVK`)
   - Minimum required revision: Rev **

## Hardware setup

This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.

Please ensure below jumper and pin configuration on board.
- Ensure BOOT SW should be in 'High'/ON position. 
    > **Note:** For KIT_PSOCE84_EVK rev. **, BOOT SW pin is BOOT.1 (P17.6).
- Ensure J20 and J21 should be in Tristate/Not-Connected (NC) position.

---------------------------------------------------------

© Thai Embedded Systems Association 2025