/***************************************************************************//**
* \file pse84_s_flash.ld
* \version 1.0.0
*
* Linker file for the GNU C compiler.
*
* The main purpose of the linker script is to describe how the sections in the
* input files should be mapped into the output file, and to control the memory
* layout of the output file.
*
* \note The entry point location starts at 0x14000000. The valid
* application image should be placed there.
*
* \note The linker files included with the PDL template projects must be generic
* and handle all common use cases. Your project may not use every section
* defined in the linker files. In that case you may see warnings during the
* build process. In your project, you can simply comment out or remove the
* relevant code in the linker file.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
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
*******************************************************************************/

OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)
ENTRY(S_Reset_Handler)

INCLUDE ../../config/GeneratedSource/cymem_gnu_CM33_0_S.ld

PROVIDE(__StackSize = 0x1000);

MEMORY
{
    INCLUDE ../../config/GeneratedSource/cymem_gnu_regions_CM33_0_S.ld
}

SECTIONS
{
    .appText_1 :
    {
        KEEP(*(.vectors))
        *(.text*)

        KEEP(*(.init))
        KEEP(*(.fini))
        /* .ctors */
        *crtbegin.*(.ctors)
        *crtbegin?.*(.ctors)
        *(EXCLUDE_FILE(*crtend?.* *crtend.*) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)
        /* .dtors */
        *crtbegin.*(.dtors)
        *crtbegin?.*(.dtors)
        *(EXCLUDE_FILE(*crtend?.* *crtend.*) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);

        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        /* Read only data */
        *(.rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
    } > code_1_C_S

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > code_1_C_S

    __exidx_start = .;

    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > code_1_C_S

    __exidx_end = .;

    .copy.table : ALIGN(4)
    {
        __copy_table_start__ = .;
        LONG (LOADADDR(.data))
        LONG (__data_start__)
        LONG ((__data_end__ - __data_start__)/4)

        LONG(LOADADDR(.appText_2))
        LONG(CYMEM_CM33_0_S_code_2_START)
        LONG((__cy_sram0_code_vma_end__ - __cy_sram0_code_vma_start__)/4)
        __copy_table_end__ = .;
    } > code_1_C_S

    /* To clear multiple BSS sections,
     * uncomment .zero.table section and,
     * define __STARTUP_CLEAR_BSS_MULTIPLE in CAT1B devices */
    .zero.table : ALIGN(4)
    {
        __zero_table_start__ = .;
        LONG (__bss_start__)
        LONG ((__bss_end__ - __bss_start__)/4)
        __zero_table_end__ = .;
    } > code_1_C_S

    .gnu.sgstubs : ALIGN(32)
    {
        _start_sg = .;
        *(.gnu.sgstubs*)
        . = ALIGN(32);
        _end_sg = .;
    } > codeNsc_C_S

    .ramVectors (NOLOAD):
    {
        __ram_vectors_start__ = .;
        KEEP(*(.ram_vectors))
        __ram_vectors_end__   = .;
    } > data_1_S

    .data : ALIGN(4)
    {
        __data_start__ = .;
        *(.data*)
        KEEP(*(.jcr*))
        . = ALIGN(4);
        __data_end__ = .;
    } > data_1_S AT>code_1_C_S

    .bss (NOLOAD): ALIGN(4)
    {
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > data_1_S

    .noinit (NOLOAD) :
    {
        KEEP(*(.noinit))
    } > data_1_S

    .heap (NOLOAD): ALIGN(8)
    {
        __HeapBase = .;
        __end__ = .;
        end = __end__;
        KEEP(*(.heap*))
        . = ALIGN(8);
        . = ORIGIN(data_1_S) + LENGTH(data_1_S) - __StackSize;
        __HeapLimit = .;
    } > data_1_S

    .appText_2 : ALIGN(4)
    {
        __cy_sram0_code_vma_start__ = .;
        KEEP(*(.cy_ramfunc*))
        . = ALIGN(4);
        __cy_sram0_code_vma_end__ = .;
    } > code_2_C_S AT>code_1_C_S

    .cy_sharedmem_sec (NOLOAD):
    {
        __sec_ram_start__ = .;
        KEEP(*(.cy_sharedmem_sec))
        __sec_ram_end__ = .;
    } > shared_mem0_S

    .cy_sharedmem (NOLOAD):
    {
        __public_ram_start__ = .;
        KEEP(*(.cy_sharedmem))
        __public_ram_end__ = .;
    } > shared_mem1_S

    __StackTop = ORIGIN(data_1_S) + LENGTH(data_1_S);
    __StackLimit = __StackTop - __StackSize;
    PROVIDE(__stack = __StackTop);

    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
}
