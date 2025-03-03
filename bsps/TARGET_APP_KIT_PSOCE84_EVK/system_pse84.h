/***************************************************************************//**
* \file system_pse84.h
* \version 1.0
*
* \brief Device system header file.
*
********************************************************************************
* \copyright
* Copyright 2016-2023 Cypress Semiconductor Corporation
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
*******************************************************************************/


#ifndef _SYSTEM_PSE84_H_
#define _SYSTEM_PSE84_H_

/**
* \addtogroup group_system_config_1d
* \{
* Provides device startup, system configuration, and linker script files.
* The system startup provides the followings features:
* - \ref group_system_config_device_memory_definition_1d
* - \ref group_system_config_device_initialization_1d
* - \ref group_system_config_memory_configurator_1d
* - \ref group_system_config_heap_stack_config_1d
* - \ref group_system_config_default_handlers_1d
* - \ref group_system_config_device_vector_table_1d
*
* \section group_system_config_configuration_1d Configuration Considerations
*
* \subsection group_system_config_device_memory_definition_1d Device Memory Definition
* Allocation of different types of memory such as the ROM, flash and RAM etc. for the CPU is defined by the linker scripts.
*
* \note The linker files provided with the PDL are generic and handle all common
* use cases. Your project may not use every section defined in the linker files.
* In that case you may see warnings during the build process. To eliminate build
* warnings in your project, you can simply comment out or remove the relevant
* section in the linker file.
*
* <b>ARM GCC</b>\n
* The flash and RAM sections for the CPU are defined in the linker files:
* 'xx_yy_zz.ld', where 'xx' is the device group, 'yy' is the secure or non secure,
* and zz is the memory type; for example, 'pse84_ns_ram.ld' and 'pse84_s_flash.ld'.
* \note If the start of the Cortex-M33 application image is changed, the value
* of the \ref CY_CORTEX_M33_SEC_APPL_ADDR should also be changed. The
* \ref CY_CORTEX_M33_SEC_APPL_ADDR macro should be used as the parameter for the
* Cy_SysEnableCM33() function call.
*
* \note If the start of the Cortex-M55 application image is changed, the value
* of the \ref CY_CORTEX_M55_APPL_ADDR should also be changed. The
* \ref CY_CORTEX_M55_APPL_ADDR macro should be used as the parameter for the
* Cy_SysEnableCM55() function call.
*
* Change the code and data sizes by editing the macros values in the
* linker files for both CM33 and CM55 CPUs:
* - 'pse84_ns_zz.ld', where 'zz' is the device memory type:
* \code
*   code       (rx)     : ORIGIN = CODE_VMA, LENGTH = CODE_SIZE
*   data       (rwx)    : ORIGIN = DATA_VMA, LENGTH = DATA_SIZE
* \endcode
* 
* \subsection group_system_config_memory_configurator_1d Memory Configurator
* \note This feature is available  for CAT1D devices at the moment, only for 'Flash' applications and
*  for GCC compiler.
* This feature of the Device Configurator allows you to visually explore and edit memory
* regions, that are allocated for the project with separation per cores with possibility
* to use one region for more than one core.
* Memory regions are grouped by the memory type.
* For more information about it, please refer to the Infineon Device Configurator user guide.
* \note When created or edited, the memory region starting address is the address within each
*  memory block, not the global address.
*
* \note If the memory region is created or deleted, it's usage should be created or deleted
* from the linker script.
* 
* <b>Default memory regions:</b>\n
* <table>
* <tr><th>Region name<th>Offset<th>Size<th>Core(s)
* <tr><td align="center" colspan="4"><b>Instruction Tightly Coupled Memory (ITCM)</b></td>
* <tr><td>code_4<td>0x0<td>0x40000<td>CM55
* <tr><td align="center" colspan="4"><b>Data Tightly Coupled Memory (DTCM)</b></td>
* <tr><td>data_2<td>0x0<td>0x40000<td>CM55
* <tr><td align="center" colspan="4"><b>RRAM</b></td>
* <tr><td>code_8<td>0xF400<td>0x1AB00<td>CM33(s)
* <tr><td align="center" colspan="4"><b>SRAM</b></td>
* <tr><td>code_2<td>0x1000<td>0x7000<td>CM33(ns), CM33(s)
* <tr><td>data_1<td>0x8000<td>0x4B000<td>CM33(s)
* <tr><td>shared_mem0<td>0x54000<td>0x1000<td>CM33(s)
* <tr><td>data_2_ns<td>0x55000<td>0x2B000<td>CM33(ns)
* <tr><td>code_4_ns<td>0x80000<td>0x40000<td>CM33(ns)
* <tr><td>data_1_ns<td>0xC0000<td>0x3E000<td>CM33(ns)
* <tr><td>shared_mem1<td>0xFE000<td>0x800<td>CM33(s)
* <tr><td>shared_mem0_ns<td>0xFE800<td>0x800<td>CM33(ns)
* <tr><td>shared_mem2<td>0xFF000<td>0x1000<td>CM55
* <tr><td align="center" colspan="4"><b>System SRAM (SoCMEM)</b></td>
* <tr><td>code_6<td>0x0<td>0x80000<td>CM55
* <tr><td>gpu_buf<td>0x80000<td>0x80000<td>CM33(ns), CM55
* <tr><td>shared_mem1_ns<td>0x100000<td>0x100000<td>CM33(ns), CM55
* <tr><td>data_3<td>0x200000<td>0x100000<td>CM55
* <tr><td>code_5_ns<td>0x300000<td>0x100000<td>CM33(ns)
* <tr><td>data_3_ns<td>0x400000<td>0x100000<td>CM33(ns)
* <tr><td align="center" colspan="4"><b>Serial Memory Interface block 0, memory 1</b></td>
* <tr><td>code_1<td>0x100400<td>0x3FB00<td>CM33(ns), CM33(s)
* <tr><td>codeNsc<td>0x13FF00<td>0x100<td>CM33(ns), CM33(s)
* <tr><td>code_1_ns<td>0x340400<td>0x1FFC00<td>CM33(ns)
* <tr><td>code_3<td>0x580400<td>0x2FFC00<td>CM55
* </table>
* 
* If you want to remove the memory region, you will need to find the region in question used in the default linker
* scripts. For example, if you want to remove code_2 region:
* 1. Remove it in the Device Configurator Memory tab. (located in the SRAM memory)
* 2. Search in the folder [Project_folder] for 'code_2' in *.ld files. Search reveals usage in only one
* file: 'pse84_s_flash.ld' in the folder located at
* '[Project_folder]bsps/TARGET_APP_KIT_PSOCE84_EVK/COMPONENT_CM33/TOOLCHAIN_GCC_ARM/'
* 3. Open the linker script located from the previous step and search for 'code_2' to find all usage of this region:
*     -# Line 121 of pse84_s_flash.ld file: The symbol 'CYMEM_CM33_0_S_code_2_START': make sure that this symbol is
* not used in the linker scripts and/or source code. If not - it safe to remove it
*     -# Line 186 of pse84_s_flash.ld file: Placement of the section .appText_2 in that region and placing cy_ramfunc
* to it, it has to be moved
* 
*
* \subsection group_system_config_device_initialization_1d Device Initialization
* After a power-on-reset (POR), the boot process is handled by the boot code
* from the on-chip ROM that is always executed by the Cortex-M0+ core. The boot
* code passes the control to the Cortex-M33 startup code and Cortex-M33 boots the Cortex-M55 core.
*
* <b>CM33 Boot</b><br/>
* CM33 always boots in secure mode after reset. Then, the secure code switches
* execution to non-secure mode. Each execution environment has its own application image.
* Each application image contains its startup code. So, there are two separate startup codes.
* One is for secure execution environment, part of secure application image and
* other one is for non-secure execution environment, part of non-secure application image.
* Execution of startup code is triggered by the secure code after it completes the
* initialization during boot process. It switches control to non-secure startup code
* by switching processor execution state to non-secure state.\n
* The secure code is programmed in RRAM NVM MAIN region. This code executes in place (XIP) from RRAM.
* First secure code to execute on CM33 is CM33_L1_BOOTLOADER. The CM33_L1_BOOTLOADER, SE_RRAM_BOOT
* code is launched by the code executing on CM0P core in secure enclave by setting the address of
* the image entry point in the CM33_S_VECTOR_TABLE_BASE (S_VTOR) register and setting the CM33_CTL.CPUWAIT
* to LOW to allow execution of reset handler of secure image. Address of CM33_L1_BOOTLOADER image entry point
* is obtained from the TOC2 table entry CM33_L1_BOOTLOADER_ADDR.
*
* <b>CM55 Boot</b><br/>
* The CM55 CPUSS is OFF by default upon POR. CM55 application is launched from CM33 non-secure application
* depending on the use case requirements. CM55 Application is programmed executed in place from the external flash.
* The C runtime code will copy necessary code to SOCMEM and other memory areas depending on the choice made for the
* execution region in the linker script.
* CM55 execution is held by its CM55_CTL.CPU_WAIT (which will be HIGH) till released (made LOW) by CM33 app
* to launch the CM55 code after programming the CM55 VTOR with the image entry point in the targeted memory.
*
* Below sequence diagram captures the initialization process in the startup code.
* ![](cm33_bootup_sequence.png)
*
* \subsection group_system_config_heap_stack_config_1d Heap and Stack Configuration
* By default, the stack size is set to 0x00001000 and the entire remaining ram is used for the heap
*
* \subsubsection group_system_config_heap_stack_config_gcc_1d ARM GCC
* - <b>Editing source code</b>\n
* The stack and heap sizes are defined in the linker script file: 'pse84_ns_ram.ld'.
* Change the stack size by modifying the following line:\n
* \code STACK_SIZE = 0x00001000; \endcode
* Remaining free RAM is used as heap.
*
* \note Correct operation of malloc and related functions depends on the working
* implementation of the 'sbrk' function. Newlib-nano (default C runtime library
* used by the GNU Arm Embedded toolchain) provides weak 'sbrk' implementation that
* doesn't check for heap and stack collisions during excessive memory allocations.
* To ensure the heap always remains within the range defined by __HeapBase and
* __HeapLimit linker symbols, provide a strong override for the 'sbrk' function:
* \snippet startup/snippet/main.c snippet_sbrk_cm33
* For FreeRTOS-enabled multi-threaded applications, it is sufficient to include
* clib-support library that provides newlib-compatible implementations of
* 'sbrk', '__malloc_lock' and '__malloc_unlock':
* <br>
* https://github.com/Infineon/clib-support.
*
* \subsubsection group_system_config_heap_stack_config_arm_1d ARM Compiler
* Currently Not Supported
*
* \subsubsection group_system_config_heap_stack_config_iar_1d IAR
* Currently Not Supported
*
* \subsection group_system_config_default_handlers_1d Default Interrupt Handlers Definition
* The default interrupt handler functions are dummy handler in the startup file.\n
* Below is the default handler for the non-secure interrupts:\n
* \code interrupt_type void InterruptHandler(void) {
*    while(1);
* } \endcode
*
* \subsection group_system_config_device_vector_table_1d Vectors Table Copy from Flash to RAM
* This process uses memory sections defined in the linker script. The startup code copies the
* default vector table contents to the non-secure SRAM region specified by the linker script.
* APIs are provided in the sysint driver to hook user implemented handler replacing the default
* handler for the corresponding interrupt.
*
* Following tables provide the address of the default and non-secure SRAM interrupt vector
* table for different supported compilers.
* \subsubsection group_system_config_device_vector_table_gcc_1d ARM GCC
* The linker script file is 'pse84_ns_ram.ld'.
* For non-secure world, it uses the following variable.\n
*       Copy interrupt vectors from ROM/flash to RAM: \n
*       From: \code __ns_vector_table \endcode
*       To:   \code __ns_vector_table_rw \endcode
* The vector table address (and the vector table itself) are defined in the
* ns_start_<device>.c startup file corresponding to non-secure world.
* The code in these files copies the vector table from ROM/Flash to RAM.
*
* \subsubsection group_system_config_device_vector_table_mdk_1d ARM Compiler
* Currently Not Supported
*
* \subsubsection group_system_config_device_vector_table_iar_1d IAR
* Currently Not Supported
*
* \defgroup group_system_config_macro_1d Macros
* \{
*   \defgroup group_system_config_system_macro_1d System Macros
*   \defgroup group_system_config_core_status_macro_1d Core Status Macros
*   \defgroup group_system_config_user_settings_macro_1d User Settings Macros
* \}
* \defgroup group_system_config_functions_1d Functions
* \{
*   \defgroup group_system_config_cm33_functions_1d Cortex-M33 Control Functions
*   \defgroup group_system_config_cm55_functions_1d Cortex-M55 Control Functions
* \}
* \defgroup group_system_config_globals_1d Global Variables
*
* \}
*/

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
* Include files
*******************************************************************************/
#include <stdint.h>


/*******************************************************************************
* Global preprocessor symbols/macros ('define')
*******************************************************************************/

/*******************************************************************************
*
*                      START OF USER SETTINGS HERE
*                      ===========================
*
*                 All lines with '<<<' can be set by user.
*
*******************************************************************************/

/**
* \addtogroup group_system_config_system_macro_1d
* \{
*/
#if (CY_SYSTEM_CPU_CM33 == 1UL) || defined(CY_DOXYGEN)
    /** The Cortex-M33 startup driver identifier */
    #define CY_STARTUP_M33_ID               ((uint32_t)((uint32_t)((0x10U) & 0x3FFFU) << 18U))
#endif /* (CY_SYSTEM_CPU_CM33 == 1UL) */


#if (CY_SYSTEM_CPU_CM55 == 1UL) || defined(CY_DOXYGEN)
    /** The Cortex-M55 startup driver identifier */
    #define CY_STARTUP_M55_ID               ((uint32_t)((uint32_t)((0x11U) & 0x3FFFU) << 18U))
#endif /* (CY_SYSTEM_CPU_CM55 == 1UL) */
/** \} group_system_config_system_macro_1d */



extern void SystemInit(void);

extern void SystemCoreClockUpdate(void);

extern void     Cy_SystemInit(void);

extern uint32_t cy_delayFreqHz;
extern uint32_t cy_delayFreqKhz;
extern uint32_t  cy_delayFreqMhz;


#if (CY_SYSTEM_CPU_CM33 == 1UL) || defined(CY_DOXYGEN)
/** \addtogroup group_system_config_globals_1d
* \{
*/
#elif (CY_SYSTEM_CPU_CM55 == 1UL) || defined(CY_DOXYGEN)
/** \addtogroup group_system_config_globals_1d
* \{
*/
#endif
extern uint32_t SystemCoreClock;
extern uint32_t cy_Hfclk0FreqHz;
extern uint32_t cy_PeriClkFreqHz;
extern uint32_t cy_AhbFreqHz;
extern bool cy_WakeupFromWarmBootStatus;

#if (CY_SYSTEM_CPU_CM33 == 1UL) || defined(CY_DOXYGEN)
/** \} group_system_config_globals_1d */
#elif (CY_SYSTEM_CPU_CM55 == 1UL) || defined(CY_DOXYGEN)
/** \} group_system_config_globals_1d */
#endif

#ifdef __cplusplus
}
#endif

/** \endcond */

#endif /* _SYSTEM_PSE84_H_ */


/* [] END OF FILE */


