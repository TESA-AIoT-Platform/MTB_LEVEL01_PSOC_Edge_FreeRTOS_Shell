/***************************************************************************//**
* \file pse84_ns_flash.ld
* \version 1.0.0
*
* Linker file for the GNU C compiler.
*
* The main purpose of the linker script is to describe how the sections in the
* input files should be mapped into the output file, and to control the memory
* layout of the output file.
*
* \note The entry point location starts at 0x0200E000. The valid
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
GROUP(-lgcc -lc -lnosys )
SEARCH_DIR(.)
GROUP(libgcc.a libc.a libm.a libnosys.a)

ENTRY(Reset_Handler)

PROVIDE(__StackSize = 0x1000);

INCLUDE ../../config/GeneratedSource/cymem_gnu_CM55_0.ld


MEMORY
{
    INCLUDE ../../config/GeneratedSource/cymem_gnu_regions_CM55_0.ld
}

__app_text1_vma__           = CYMEM_CM55_0_code_3_START;
__app_text2_vma__           = CYMEM_CM55_0_code_4_INTERNAL_START;
__app_text3_vma__           = CYMEM_CM55_0_code_6_START;
__data1_vma__               = CYMEM_CM55_0_data_2_INTERNAL_START;
__data2_vma__               = CYMEM_CM55_0_data_3_START;

RAMVECTORS_ALIGNMENT        = 1024;


SECTIONS
{
    __app_text1_lma__           = CYMEM_CM55_0_code_3_START;
    .appText_1 __app_text1_vma__ : AT (__app_text1_lma__)
    {
        . = ALIGN(4);
         __text_begin = .;
        __Vectors = . ;
        KEEP(*(.vectors))
        . = ALIGN(4);
        __Vectors_End = .;
        . = ALIGN(4);
        KEEP(*(.init))
        KEEP(*(.fini))
        /* .ctors */
        *crtbegin.*(.ctors)
        *crtbegin?.*(.ctors)
        *(EXCLUDE_FILE(*crtend?.* *crtend.*) .ctors)
        *(EXCLUDE_FILE(*cy_smif.* *cy_syslib.* *cy_syslib_ext.* *cy_smif_memslot.* *cy_smif_sfdp.* *cy_smif_hb_flash.* *cyhal_qspi.*) .text*)
        *(SORT(.ctors.*))
        *(.ctors)
        /* .dtors */
        *crtbegin.*(.dtors)
        *crtbegin?.*(.dtors)
        *(EXCLUDE_FILE(*crtend?.* *crtend.*) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)
        /* Read only data */
        *(.rodata .rodata.* .constdata .constdata.* .conststring .conststring.*)
        . = ALIGN(4);
        __text_end = .;
    } > code_3

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > code_3

    __exidx_start = .;

    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > code_3

    __exidx_end = .;
    . = ALIGN(4);

    __copy_table_start__ = .;

    .copy.table : AT (__copy_table_start__ + (__app_text1_lma__ - __app_text1_vma__))
    {
        /* Copy vector table to RAM */
        /* From */
        /* To   */
        /* Size */
        LONG(__data1_lma__)
        LONG(__data1_vma__)
        LONG ((__data_end__ - __data_start__)/4)

        LONG (__data2_lma__)
        LONG (__data2_vma__)
        LONG ((__cy_socmem_data_vma_end__ - __cy_socmem_data_vma_start__)/4)

        LONG (__app_text2_lma__)
        LONG (__app_text2_vma__)
        LONG ((__cy_itcm_vma_end__ - __cy_itcm_vma_start__)/4)

        LONG (__app_text3_lma__)
        LONG (__app_text3_vma__)
        LONG ((__cy_socmem_code_vma_end__ - __cy_socmem_code_vma_start__)/4)

        __copy_table_end__ = .;
    } > code_3

    . = ALIGN(4);
    __zero_table_start__ = . ;
    /* To clear multiple BSS sections */
    .zero.table :
    {
        LONG (__bss_start__)
        LONG ((__bss_end__ - __bss_start__)/4)
        __zero_table_end__ = .;

    } > code_3
    __app_text1_lma_count__ = .  + (__app_text1_lma__ - __app_text1_vma__);

    /* Linker throws error hence the below check is reduandant */
    /* ASSERT((__app_text1_lma_count__ - __app_text1_lma__) <= CODE_1_SIZE, "CM55 Image can't fit in the slot. Increase CODE_1_SIZE") */

    __app_text2_lma__ = __app_text1_lma_count__;
    .appText_2 __app_text2_vma__ : AT(__app_text2_lma__)
    {
        . = ALIGN(4);
         __cy_itcm_vma_start__ = .;
        KEEP(*(.cy_itcm))
        *cy_syslib.*(.text*)
        *cy_syslib_ext.*(.text*)
        *cy_smif.*(.text*)
        *cy_smif_memslot.*(.text*)
        *cy_smif_sfdp.*(.text*)
        *cy_smif_hb_flash.*(.text*)
        *cyhal_qspi.*(.text*)
        . = ALIGN(4);
        __cy_itcm_vma_end__ = .;

    }  > code_4_INTERNAL
    __app_text1_lma_count__ = .  + (__app_text2_lma__ - __app_text2_vma__);

    .ram_vectors (NOLOAD):
    {
        . = ALIGN(RAMVECTORS_ALIGNMENT);
        __ram_vectors_start__ = .;
        KEEP(*(.ram_vectors))
        __ram_vectors_end__   = .;
    } > code_4_INTERNAL

    __app_text3_lma__ = __app_text1_lma_count__;
    .appText_3 __app_text3_vma__ : AT(__app_text3_lma__)
    {
        . = ALIGN(4);
         __cy_socmem_code_vma_start__ = .;
        KEEP(*(.cy_socmem_code))
        . = ALIGN(4);
        __cy_socmem_code_vma_end__ = .;
    }  > code_6
    __app_text1_lma_count__ = .  + (__app_text3_lma__ - __app_text3_vma__);

    __data1_lma__ = __app_text1_lma_count__;
    .data __data1_vma__ : AT(__data1_lma__)
    {
        . = ALIGN(4);
        __data_start__ = .;

        *(vtable)
        *(.data*)

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

        KEEP(*(.jcr*))
        . = ALIGN(4);

        __data_end__ = .;
    } > data_2_INTERNAL
    __app_text1_lma_count__ = .  + (__data1_lma__ - __data1_vma__);

    .noinit (NOLOAD) : ALIGN(8)
    {
        KEEP(*(.noinit))
         . = ALIGN(4);
     __noinit_end__   = .;
    } > data_2_INTERNAL

    .bss (NOLOAD):
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > data_2_INTERNAL

    . = ALIGN(32);
    __StackTop = ORIGIN(data_2_INTERNAL) + LENGTH(data_2_INTERNAL);
    __StackLimit = __StackTop - __StackSize;
    PROVIDE(__stack = __StackTop);

    /* Check if data + heap + stack exceeds RAM limit */
    /* Below check is only valid when Stack and Heap are in same memory */
    /* ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack") */

    __data2_lma__ = __app_text1_lma_count__;
    .data_2_INTERNAL __data2_vma__ : AT(__data2_lma__)
    {
        . = ALIGN(4);
         __cy_socmem_data_vma_start__ = .;
        KEEP(*(.cy_socmem_data))
        . = ALIGN(4);
        __cy_socmem_data_vma_end__ = .;

    }  > data_3
    __app_text1_lma_count__ = .  + (__data2_vma__ - __data2_lma__);

    .heap (NOLOAD):
    {
        . = ALIGN(8);
        __HeapBase = .;
        __end__ = .;
        end = __end__;
        KEEP(*(.heap*))
        . = ALIGN(8);
        . = ORIGIN(data_3) + LENGTH(data_3);
        __HeapLimit = .;
    } > data_3

    .reserved_socmem (NOLOAD):
    {
      . = . + CYMEM_CM55_0_shared_mem1_ns_SIZE; /* reserved socmem memory */
    }  > shared_mem1_ns

    .cy_gpu_buf (NOLOAD):
    {
      KEEP(*(.cy_gpu_buf))
    }  > gpu_buf

    .cy_sharedmem (NOLOAD):
    {
        . = ALIGN(4);
        __public_ram_start__ = .;
        KEEP(*(.cy_sharedmem))
        . = ALIGN(4);
        __public_ram_end__ = .;
    } > shared_mem2
}
