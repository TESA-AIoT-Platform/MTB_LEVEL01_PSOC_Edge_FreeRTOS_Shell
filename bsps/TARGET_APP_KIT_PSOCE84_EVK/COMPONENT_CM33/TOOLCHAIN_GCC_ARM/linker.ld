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
ENTRY(Reset_Handler)

PROVIDE(__StackSize = 0x1000);

INCLUDE ../../config/GeneratedSource/cymem_gnu_CM33_0.ld

MEMORY
{
    INCLUDE ../../config/GeneratedSource/cymem_gnu_regions_CM33_0.ld
}

SECTIONS
{
    .appText_1 :
    {
        KEEP(*(.vectors))
        *(EXCLUDE_FILE(*cy_syslib.* *cy_syslib_ext.* *cy_smif.* *cy_smif_memslot.* *cy_smif_sfdp.* *cy_smif_hb_flash.* *cyhal_qspi.*)  .text*)
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
    	ASSERT(ADDR(.appText_1)-ORIGIN(code_1_ns_C) == LOADADDR(.appText_1)-ORIGIN(code_1_ns), "load address mismatch for .appText_1");
    } > code_1_ns_C AT>code_1_ns

    .ARM.extab : ALIGN(4)
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
        ASSERT(ADDR(.ARM.extab)-ORIGIN(code_1_ns_C) == LOADADDR(.ARM.extab)-ORIGIN(code_1_ns), "load address mismatch for .ARM.extab");
    } > code_1_ns_C AT>code_1_ns

    .ARM.exidx : ALIGN(4)
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
        ASSERT(ADDR(.ARM.exidx)-ORIGIN(code_1_ns_C) == LOADADDR(.ARM.exidx)-ORIGIN(code_1_ns), "load address mismatch for .ARM.exidx");
    } > code_1_ns_C AT>code_1_ns

    .copy.table : ALIGN(4)
    {
        __copy_table_start__ = .;
        LONG(LOADADDR(.cy_sram_code))
        LONG(__cy_sram_code_vma_start__)
        LONG((__cy_sram_code_vma_end__ - __cy_sram_code_vma_start__)/4)

        LONG (LOADADDR(.data))
        LONG (__data_start__)
        LONG ((__data_end__ - __data_start__)/4)

        LONG (LOADADDR(.data_2))
        LONG (__cy_sram0_datans_vma_start__)
        LONG ((__cy_sram0_datans_vma_end__ - __cy_sram0_datans_vma_start__)/4)

        LONG (LOADADDR(.data_3))
        LONG (__cy_socmem_data_vma_start__)
        LONG ((__cy_socmem_data_vma_end__ - __cy_socmem_data_vma_start__)/4)

        LONG(LOADADDR(.appText_4))
        LONG(CYMEM_CM33_0_code_4_ns_START)
        LONG((__cy_sram1_code_vma_end__ - __cy_sram1_code_vma_start__)/4)              /* Size */

        LONG(LOADADDR(.appText_5))
        LONG(CYMEM_CM33_0_code_5_ns_START)
        LONG((__cy_socmem_code_vma_end__ - __cy_socmem_code_vma_start__)/4)              /* Size */

        __copy_table_end__ = .;
        ASSERT(ADDR(.copy.table)-ORIGIN(code_1_ns_C) == LOADADDR(.copy.table)-ORIGIN(code_1_ns), "load address mismatch for .copy.table");
    } > code_1_ns_C AT>code_1_ns

    .zero.table : ALIGN(4)
    {
        __zero_table_start__ = . ;
        LONG (__bss_start__)
        LONG ((__bss_end__ - __bss_start__)/4)
        __zero_table_end__ = .;
        ASSERT(ADDR(.zero.table)-ORIGIN(code_1_ns_C) == LOADADDR(.zero.table)-ORIGIN(code_1_ns), "load address mismatch for .zero.table");
    } > code_1_ns_C AT>code_1_ns

    .appText_4 : ALIGN(4)
    {
         __cy_sram1_code_vma_start__ = .;
        KEEP(*(.cy_sram1_code))
        KEEP(*(.cy_ramfunc))
        KEEP(*(.text.cy_os_common))
        *cy_syslib_ext.*(.text*)
        *cy_syslib.*(.text*)
        *cy_smif.*(.text*)
        *cy_smif_memslot.*(.text*)
        *cy_smif_sfdp.*(.text*)
        *cy_smif_hb_flash.*(.text*)
        *cyhal_qspi.*(.text*)
        . = ALIGN(4);
        __cy_sram1_code_vma_end__ = .;
    }  > code_4_ns_C AT>code_1_ns

    .appText_5 : ALIGN(4)
    {
         __cy_socmem_code_vma_start__ = .;
        KEEP(*(.cy_socmem_code))
        . = ALIGN(4);
        __cy_socmem_code_vma_end__ = .;
    }  > code_5_ns_C AT>code_1_ns

    .ram_vectors (NOLOAD):
    {
        __ram_vectors_start__ = .;
        KEEP(*(.ram_vectors))
        __ram_vectors_end__   = .;
    } > data_1_ns

    .cy_sram_code : ALIGN(4)
    {
         __cy_sram_code_vma_start__ = .;
        KEEP(*(.cy_sram_code))
        KEEP(*(.text.cy_os_common))
        . = ALIGN(4);
        __cy_sram_code_vma_end__ = .;
    } > data_1_ns AT>code_1_ns

    .data : ALIGN(4)
    {
	    __data_start__ = .;
        *(.data*)      /* Data memory */
        KEEP(*(.jcr*))
        . = ALIGN(4);
	    __data_end__ = .;
    } > data_1_ns AT>code_1_ns

    .bss (NOLOAD): ALIGN(4)
    {
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > data_1_ns

    .noinit (NOLOAD) :
    {
        KEEP(*(.noinit))
    } > data_1_ns

    .heap (NOLOAD): ALIGN(8)
    {
        __HeapBase = .;
        __end__ = .;
        end = __end__;
        KEEP(*(.heap*))
        . = ALIGN(8);
        . = ORIGIN(data_1_ns) + LENGTH(data_1_ns) - __StackSize;
        __HeapLimit = .;
    } > data_1_ns

    .cy_sharedmem (NOLOAD):
    {
        . = ALIGN(4);
        __public_ram_start__ = .;
        KEEP(*(.cy_sharedmem))
        . = ALIGN(4);
        __public_ram_end__ = .;
    } > shared_mem0_ns

    .cy_shared_socmem (NOLOAD):
    {
        . = ALIGN(4);
        __public_ram_socmem_start__ = .;
        KEEP(*(.cy_shared_socmem))
        . = ALIGN(4);
        __public_ram_socmem_end__ = .;
    } > shared_mem1_ns

    __StackTop = ORIGIN(data_1_ns) + LENGTH(data_1_ns);
    __StackLimit = __StackTop - __StackSize;
    PROVIDE(__stack = __StackTop);

    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")

    .data_2 : ALIGN(4)
    {
         __cy_sram0_datans_vma_start__ = .;
        KEEP(*(.cy_sram0_data_ns))
        . = ALIGN(4);
        __cy_sram0_datans_vma_end__ = .;
    }  > data_2_ns AT>code_1_ns

    .data_3 : ALIGN(4)
    {
         __cy_socmem_data_vma_start__ = .;
        KEEP(*(.cy_socmem_data))
        . = ALIGN(4);
        __cy_socmem_data_vma_end__ = .;
    }  > data_3_ns AT>code_1_ns

    .cy_gpu_buf (NOLOAD):
    {
        KEEP(*(.cy_gpu_buf))
    }  > gpu_buf
}
