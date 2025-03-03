/***************************************************************************//**
* \file pse84_common.h
* \version 1.0.0
*
* Header file for Linker file for the armclang c compiler.
*
* The main purpose of this file is to describe how the sections in the
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
* Copyright (c) (2020-2023), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License")
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

/*-----------------------------------------------------------------------------------*/
/* Common definitions for the device                                                 */
/*-----------------------------------------------------------------------------------*/

#define ITCM_NS_START                    0x00000000
#define ITCM_S_START                     0x10000000
#define ITCM_SIZE                        0x00040000

#define DTCM_NS_START                    0x20000000
#define DTCM_S_START                     0x30000000
#define DTCM_SIZE                        0x00040000

#define RRAM_NVM_MAIN_NS_START           0x22000000
#define RRAM_NVM_MAIN_S_START            0x32000000
#define RRAM_NVM_MAIN_NS_CBUS_START      0x02000000
#define RRAM_NVM_MAIN_S_CBUS_START       0x12000000
#define RRAM_NVM_MAIN_SIZE               0x00040000

#define RRAM_NVM_SECURE_NS_START         0x23C00000
#define RRAM_NVM_SECURE_S_START          0x33C00000
#define RRAM_NVM_SECURE_NS_CBUS_START    0x03C00000
#define RRAM_NVM_SECURE_S_CBUS_START     0x13C00000
#define RRAM_NVM_SECURE_SIZE             0x00040000

#define SRAM0_NS_SAHB_START              0x24000000
#define SRAM0_S_SAHB_START               0x34000000
#define SRAM0_NS_CBUS_START              0x04000000
#define SRAM0_S_CBUS_START               0x14000000
#define SRAM0_SIZE                       0x00080000

#define SRAM1_NS_SAHB_START              0x24080000
#define SRAM1_S_SAHB_START               0x34080000
#define SRAM1_NS_CBUS_START              0x04080000
#define SRAM1_S_CBUS_START               0x14080000
#define SRAM1_SIZE                       0x00080000

#define SOCMEMSRAM_NS_SAHB_START         0x26000000
#define SOCMEMSRAM_S_SAHB_START          0x36000000
#define SOCMEMSRAM_NS_CBUS_START         0x06000000
#define SOCMEMSRAM_S_CBUS_START          0x16000000
#define SOCMEMSRAM_SIZE                  0x00500000

#define XIP0_NS_SAHB_START               0x60000000
#define XIP0_S_SAHB_START                0x70000000
#define XIP0_NS_CBUS_START               0x08000000
#define XIP0_S_CBUS_START                0x18000000
#define XIP0_SIZE                        0x04000000

#define XIP1_NS_START                    0x64000000
#define XIP1_S_START                     0x74000000
#define XIP1_NS_CBUS_START               0x0C000000
#define XIP1_S_CBUS_START                0x1C000000
#define XIP1_SIZE                        0x04000000

/*-----------------------------------------------------------------------------------*/
#ifdef FLASH_SECTOR_SIZE
#define XIP0_SECTOR_SIZE                 FLASH_SECTOR_SIZE
#else
#define XIP0_SECTOR_SIZE                 (256 *1024) /* Default Sector size set to 256KB */
#endif

#define CM0P_RAMVECTORS_ALIGNMENT        1024
#define CM33_RAMVECTORS_ALIGNMENT        1024
#define CM55_RAMVECTORS_ALIGNMENT        1024

#define CM33S_MSP_STACK_SIZE             0x00000800
#define CM33NS_MSP_STACK_SIZE            0x00000800
#define CM55_MSP_STACK_SIZE              0x00000800

#define MSP_STACK_SIZE                   0x00001000
#define HEAP_SIZE                        0x00001000
#define CODE_NSC_SIZE                    0x00000100

#define CM33S_APP_HEADER_SIZE            0x00000400
#define CM33NS_APP_HEADER_SIZE           0x00000400
#define CM55NS_APP_HEADER_SIZE           0x00000400

#define SRAM0_SHARED_SIZE                0x00002000   /* 8K memory reserved for cm0 and cm33-sec IPC data */
#define SRAM0_SHARED_CM0_SIZE            0x00001000   /* Out of 8K shared memory, 4K is reserved for CM0 */

#define SRAM1_SHARED_SIZE                0x00002000   /* 8K memory reserved for cm33-s, cm33-ns and cm55 IPC data */
#define SRAM1_SHARED_CM33NS_SIZE         0x00000800   /* Out of 8K shared memory, 2K is reserved for CM33-S */
#define SRAM1_SHARED_CM33S_SIZE          0x00000800   /* Out of 8K shared memory, 2K is reserved for CM33-S */

#define XIP0_CM33S_SLOT_SIZE             (512 * 1024) /* Slot size is set to 512 KB */
#define XIP0_CM33S_IMAGE_OFFSET          0x00100000
#define XIP0_CM33S_APP_OFFSET            (XIP0_CM33S_IMAGE_OFFSET + CM33S_APP_HEADER_SIZE)
ScatterAssert(2*XIP0_SECTOR_SIZE <= XIP0_CM33S_SLOT_SIZE) ; /* CM33 S Image can't fit in the slot. Increase the slot size XIP0_CM33S_SLOT_SIZE */
#define XIP0_CM33S_APP_SIZE              (XIP0_CM33S_SLOT_SIZE - CM33S_APP_HEADER_SIZE - CODE_NSC_SIZE - XIP0_SECTOR_SIZE)

#define XIP0_CM33NS_SLOT_SIZE            (2304 * 1024) /* Slot size is set to 2.25MB */
#define XIP0_CM33NS_IMAGE_OFFSET         0x00340000
#define XIP0_CM33NS_APP_OFFSET           (XIP0_CM33NS_IMAGE_OFFSET + CM33NS_APP_HEADER_SIZE)
ScatterAssert(2*XIP0_SECTOR_SIZE <= XIP0_CM33NS_SLOT_SIZE) ; /* CM33 NS Image can't fit in the slot. Increase the slot size XIP0_CM33NS_SLOT_SIZE */
#define XIP0_CM33NS_APP_SIZE             (XIP0_CM33NS_SLOT_SIZE - CM33NS_APP_HEADER_SIZE - XIP0_SECTOR_SIZE)

#define XIP0_CM55NS_SLOT_SIZE            (3328 * 1024) /* Slot size is set to 3.25MB */
#define XIP0_CM55NS_IMAGE_OFFSET         0x00580000
#define XIP0_CM55NS_APP_OFFSET           (XIP0_CM55NS_IMAGE_OFFSET + CM55NS_APP_HEADER_SIZE)
ScatterAssert(2*XIP0_SECTOR_SIZE <= XIP0_CM55NS_SLOT_SIZE) ; /* CM55 NS Image can't fit in the slot. Increase the slot size XIP0_CM55NS_SLOT_SIZE */
#define XIP0_CM55NS_APP_SIZE             (XIP0_CM55NS_SLOT_SIZE - CM55NS_APP_HEADER_SIZE - XIP0_SECTOR_SIZE)

#define RRAM_CM33S_IMAGE_OFFSET          0x0000F000
#define RRAM_CM33S_APP_OFFSET            (RRAM_CM33S_IMAGE_OFFSET + CM33S_APP_HEADER_SIZE)
#define RRAM_CM33S_APP_SIZE              0x0001AB00

#define RRAM_CM33NS_IMAGE_OFFSET         0x0002A000
#define RRAM_CM33NS_APP_OFFSET           (RRAM_CM33NS_IMAGE_OFFSET + CM33NS_APP_HEADER_SIZE)
#define RRAM_CM33NS_APP_SIZE             0

#define RRAM_CM55NS_IMAGE_OFFSET         0x00040800
#define RRAM_CM55NS_APP_OFFSET           (RRAM_CM55NS_IMAGE_OFFSET + CM55NS_APP_HEADER_SIZE)
#define RRAM_CM55NS_APP_SIZE             0

#define SRAM0_CM33S_IMAGE_OFFSET         0x00001000
#define SRAM0_CM33S_APP_OFFSET           (SRAM0_CM33S_IMAGE_OFFSET)
#define SRAM0_CM33S_APP_SIZE             (28*1024)

#define SRAM0_CM33S_DATA_OFFSET          0x00008000
#define SRAM0_CM33S_DATA_SIZE            (300*1024)

#define SRAM0_SHARED_OFFSET              0x00053000

#define SRAM0_CM33NS_IMAGE_OFFSET        0x00000000
#define SRAM0_CM33NS_APP_OFFSET          SRAM0_CM33NS_IMAGE_OFFSET
#define SRAM0_CM33NS_APP_SIZE            0x00000000

#define SRAM0_CM33NS_DATA_OFFSET         (SRAM0_SHARED_OFFSET + SRAM0_SHARED_SIZE)
#define SRAM0_CM33NS_DATA_SIZE           (SRAM0_SIZE - (SRAM0_SHARED_SIZE + SRAM0_SHARED_OFFSET))
#define SRAM0_CM55NS_IMAGE_OFFSET        0x00000000
#define SRAM0_CM55NS_APP_OFFSET          SRAM0_CM55NS_IMAGE_OFFSET
#define SRAM0_CM55NS_APP_SIZE            0x00000000

#define SRAM1_CM55NS_DATA_OFFSET         0x00000000
#define SRAM1_CM55NS_DATA_SIZE           0x00000000

#define SRAM1_CM33S_IMAGE_OFFSET         0x00000000
#define SRAM1_CM33S_APP_OFFSET           SRAM1_CM33S_IMAGE_OFFSET
#define SRAM1_CM33S_APP_SIZE             0x00000000

#define SRAM1_CM33S_DATA_OFFSET          0x00000000
#define SRAM1_CM33S_DATA_SIZE            0x00000000

#define SRAM1_CM33NS_IMAGE_OFFSET        0x00000000
#define SRAM1_CM33NS_APP_OFFSET          SRAM1_CM33NS_IMAGE_OFFSET
#define SRAM1_CM33NS_APP_SIZE            (0x00040000 - SRAM1_CM33NS_APP_OFFSET)

#define SRAM1_CM55NS_IMAGE_OFFSET        0x00000000
#define SRAM1_CM55NS_APP_OFFSET          SRAM1_CM55NS_IMAGE_OFFSET
#define SRAM1_CM55NS_APP_SIZE            0x00000000

#define SRAM1_CM33NS_DATA_OFFSET         0x00040000
#define SRAM1_CM33NS_DATA_SIZE           0x00040000 - SRAM1_SHARED_SIZE



#define SRAM1_SHARED_OFFSET             (SRAM1_CM33NS_DATA_OFFSET + SRAM1_CM33NS_DATA_SIZE)

#define SOCMEMSRAM_CM33S_IMAGE_OFFSET    0x00000000
#define SOCMEMSRAM_SEC_APP_OFFSET        SOCMEMSRAM_CM33S_IMAGE_OFFSET
#define SOCMEMSRAM_SEC_APP_SIZE          0x00000000
/*
SOCMEM Partition
--------------------------------------------------------------------
PARTITION               OFFSET                 SIZE
--------------------------------------------------------------------
CM55NS_APP            CM55NS_IMAGE_OFFSET     APP_SIZE
GPUBUF                GPUBUF_OFFSET           GPUBUF_SIZE
SHARED_MEM            SHARED_OFFSET           SHARED_SIZE
CM55NS_DATA           CM55NS_DATA_OFFSET      DATA_SIZE
CM33NS_APP            CM33NS_APP_OFFSET       CM33NS_APP_SIZE
CM33NS_DATA           CM33NS_DATA_OFFSET      CM33NS_DATA_SIZE
*/

/* APP_SOCMEMSRAM_* can be passed from application makefile to override default size using LDFLAGS+=--predefine="-DAPP_SOCMEMSRAM_*=0x0" */
#define SOCMEMSRAM_CM55NS_IMAGE_OFFSET   0x00000000
#define SOCMEMSRAM_CM55NS_APP_OFFSET     (SOCMEMSRAM_CM55NS_IMAGE_OFFSET + CM55NS_APP_HEADER_SIZE)
#if defined(APP_SOCMEMSRAM_CM55NS_APP_SIZE)
#define SOCMEMSRAM_CM55NS_APP_SIZE_DEF   APP_SOCMEMSRAM_CM55NS_APP_SIZE
#else
#define SOCMEMSRAM_CM55NS_APP_SIZE_DEF   0x00080000
#endif
#define SOCMEMSRAM_CM55NS_APP_SIZE       (SOCMEMSRAM_CM55NS_APP_SIZE_DEF - (SOCMEMSRAM_CM55NS_IMAGE_OFFSET + CM55NS_APP_HEADER_SIZE))

#define SOCMEMSRAM_GPUBUF_OFFSET         (SOCMEMSRAM_CM55NS_IMAGE_OFFSET + SOCMEMSRAM_CM55NS_APP_SIZE_DEF)
#if defined(APP_SOCMEMSRAM_GPUBUF_SIZE)
#define SOCMEMSRAM_GPUBUF_SIZE           APP_SOCMEMSRAM_GPUBUF_SIZE
#else
#define SOCMEMSRAM_GPUBUF_SIZE           0x00080000
#endif

#define SOCMEMSRAM_SHARED_OFFSET         (SOCMEMSRAM_GPUBUF_OFFSET + SOCMEMSRAM_GPUBUF_SIZE)
#if defined(APP_SOCMEMSRAM_SHARED_SIZE)
#define SOCMEMSRAM_SHARED_SIZE           APP_SOCMEMSRAM_SHARED_SIZE
#else
#define SOCMEMSRAM_SHARED_SIZE           0x00100000
#endif

#define SOCMEMSRAM_CM55NS_DATA_OFFSET    (SOCMEMSRAM_SHARED_OFFSET + SOCMEMSRAM_SHARED_SIZE)
#if defined(APP_SOCMEMSRAM_CM55NS_DATA_SIZE)
#define SOCMEMSRAM_CM55NS_DATA_SIZE           APP_SOCMEMSRAM_CM55NS_DATA_SIZE
#else
#define SOCMEMSRAM_CM55NS_DATA_SIZE      0x00100000
#endif

#define SOCMEMSRAM_CM33NS_IMAGE_OFFSET   (SOCMEMSRAM_CM55NS_DATA_OFFSET + SOCMEMSRAM_CM55NS_DATA_SIZE)
#define SOCMEMSRAM_CM33NS_APP_OFFSET     SOCMEMSRAM_CM33NS_IMAGE_OFFSET
#if defined(APP_SOCMEMSRAM_CM33NS_APP_SIZE)
#define SOCMEMSRAM_CM33NS_APP_SIZE           APP_SOCMEMSRAM_CM33NS_APP_SIZE
#else
#define SOCMEMSRAM_CM33NS_APP_SIZE       0x00100000
#endif

#define SOCMEMSRAM_CM33NS_DATA_OFFSET    (SOCMEMSRAM_CM33NS_APP_OFFSET + SOCMEMSRAM_CM33NS_APP_SIZE)
#if defined(APP_SOCMEMSRAM_CM33NS_DATA_SIZE)
#define SOCMEMSRAM_CM33NS_DATA_SIZE           APP_SOCMEMSRAM_CM33NS_DATA_SIZE
#else
#define SOCMEMSRAM_CM33NS_DATA_SIZE      0x00100000
#endif