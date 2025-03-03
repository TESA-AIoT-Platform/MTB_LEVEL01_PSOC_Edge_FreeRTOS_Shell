/***************************************************************************//**
* \file startup_cat1d.h
* \version 1.0
*
* \brief Common startup header file for CAT1D devices.
*
********************************************************************************
* \copyright
* Copyright 2016-2021 Cypress Semiconductor Corporation
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


#ifndef STARTUP_CAT1D_H_
#define STARTUP_CAT1D_H_
#include "cy_device_headers.h"

#if defined (CY_DOXYGEN) || defined (CY_DEVICE_PSE84_A0) || defined (CY_DEVICE_PSE84) /* Declarations for PSE84 */

#define CM33_FIXED_EXP_NR       (15u)
#define VECTORTABLE_SIZE        (MXCM33_SYSTEM_INT_NR + CM33_FIXED_EXP_NR + 1u) /* +1 is for Stack pointer */
#define VECTORTABLE_ALIGN       (1024) /* CM33 alignment for 195 entries (195x4=780) is 1024 bytes */

#if defined(__ARMCC_VERSION)
    typedef void(* const ExecFuncPtr)(void); /* typedef for the function pointers in the vector table */
    typedef void(* ExecFuncPtrRw)(void);
    extern ExecFuncPtrRw __s_vector_table_rw[VECTORTABLE_SIZE]    __attribute__( ( section( ".bss.noinit.RESET_RAM"))) __attribute__((aligned(VECTORTABLE_ALIGN))); /**< Secure vector table in flash/ROM */
    extern ExecFuncPtrRw __ns_vector_table_rw[VECTORTABLE_SIZE]    __attribute__( ( section( ".bss.noinit.RESET_RAM"))) __attribute__((aligned(VECTORTABLE_ALIGN)));
#elif defined (__GNUC__)
    typedef void(* ExecFuncPtr)(void) ;           /* typedef for the function pointers in the vector table */
    typedef void(* ExecFuncPtrRw)(void);
    extern ExecFuncPtrRw __s_vector_table_rw[VECTORTABLE_SIZE]   __attribute__( ( section(".ram_vectors"))) __attribute__((aligned(VECTORTABLE_ALIGN))); /**< Secure vector table in flash/ROM */
    extern ExecFuncPtrRw __ns_vector_table_rw[VECTORTABLE_SIZE]   __attribute__( ( section(".ram_vectors"))) __attribute__((aligned(VECTORTABLE_ALIGN))); /**< Secure vector table in flash/ROM */
#elif defined (__ICCARM__)
    typedef void(* const ExecFuncPtr)(void) ; /* typedef for the function pointers in the vector table */
    typedef void(* ExecFuncPtrRw)(void) ;
    extern ExecFuncPtrRw __s_vector_table_rw[VECTORTABLE_SIZE]   __attribute__( ( section(".intvec_ram"))) __attribute__((aligned(VECTORTABLE_ALIGN))); /**< Secure vector table in flash/ROM */
    extern ExecFuncPtrRw __ns_vector_table_rw[VECTORTABLE_SIZE]   __attribute__( ( section(".intvec_ram"))) __attribute__((aligned(VECTORTABLE_ALIGN))); /**< Secure vector table in flash/ROM */
#endif
extern ExecFuncPtr __s_vector_table[] ; /**< secure vector table in secure SRAM */

#endif /* defined (CY_DOXYGEN) || defined (PSE84_PSVP) */

#endif /* STARTUP_CAT1D_H_ */

