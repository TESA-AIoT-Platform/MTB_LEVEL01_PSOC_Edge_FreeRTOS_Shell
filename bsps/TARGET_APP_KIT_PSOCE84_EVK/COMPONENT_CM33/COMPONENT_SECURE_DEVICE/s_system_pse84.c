/***************************************************************************//**
* \file s_system_pse84.c
* \version 1.0
*
* The device system-source file.
*
********************************************************************************
* \copyright
* Copyright 2016-2019 Cypress Semiconductor Corporation
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

#include "cy_device.h"
#include <stdbool.h>
#include "cy_syslib.h"
#include "cy_wdt.h"
#include "cy_sysclk.h"
#include "cy_syspm_pdcm.h"



/*******************************************************************************
* SystemCoreClockUpdate()
*******************************************************************************/

/** Default HFClk frequency in Hz */
#define CY_CLK_HFCLK0_FREQ_HZ_DEFAULT       (50000000UL)

/** Default PeriClk frequency in Hz */
#define CY_CLK_PERICLK_FREQ_HZ_DEFAULT      (50000000UL)

/** Default system core frequency in Hz */
#ifdef PSE84_PSVP
#define CY_CLK_SYSTEM_FREQ_HZ_DEFAULT       (12000000UL)
#else
#define CY_CLK_SYSTEM_FREQ_HZ_DEFAULT       (50000000UL)
#endif

/**
* Holds the (Cortex-M33) system core clock,
* which is the system clock frequency supplied to the SysTick timer and the
* processor core clock.
* This variable implements CMSIS Core global variable.
* Refer to the [CMSIS documentation]
* (http://www.keil.com/pack/doc/CMSIS/Core/html/group__system__init__gr.html "System and Clock Configuration")
* for more details.
* This variable can be used by debuggers to query the frequency
* of the debug timer or to configure the trace clock speed.
*
* \attention Compilers must be configured to avoid removing this variable in case
* the application program is not using it. Debugging systems require the variable
* to be physically present in memory so that it can be examined to configure the debugger. */
uint32_t SystemCoreClock = CY_CLK_SYSTEM_FREQ_HZ_DEFAULT;

/** Holds the HFClk0 clock frequency. Updated by \ref SystemCoreClockUpdate(). */
uint32_t cy_Hfclk0FreqHz  = CY_CLK_HFCLK0_FREQ_HZ_DEFAULT;

/** Holds the PeriClk clock frequency. Updated by \ref SystemCoreClockUpdate(). */
uint32_t cy_PeriClkFreqHz = CY_CLK_PERICLK_FREQ_HZ_DEFAULT;

/** Holds the AHB frequency. Updated by \ref SystemCoreClockUpdate(). */
uint32_t cy_AhbFreqHz = CY_CLK_SYSTEM_FREQ_HZ_DEFAULT;

/*******************************************************************************
* SystemCoreClockUpdate (void)
*******************************************************************************/

/* Do not use these definitions directly in your application */
#define CY_DELAY_MS_OVERFLOW_THRESHOLD  (0x8000u)
#define CY_DELAY_1K_THRESHOLD           (1000u)
#define CY_DELAY_1K_MINUS_1_THRESHOLD   (CY_DELAY_1K_THRESHOLD - 1U)
#define CY_DELAY_1M_THRESHOLD           (1000000u)
#define CY_DELAY_1M_MINUS_1_THRESHOLD   (CY_DELAY_1M_THRESHOLD - 1U)
uint32_t cy_delayFreqHz   = CY_CLK_SYSTEM_FREQ_HZ_DEFAULT;

uint32_t cy_delayFreqKhz  = (CY_CLK_SYSTEM_FREQ_HZ_DEFAULT + CY_DELAY_1K_MINUS_1_THRESHOLD) /
                            CY_DELAY_1K_THRESHOLD;

uint32_t cy_delayFreqMhz  = (uint8_t)((CY_CLK_SYSTEM_FREQ_HZ_DEFAULT + CY_DELAY_1M_MINUS_1_THRESHOLD) /
                            CY_DELAY_1M_THRESHOLD);

#define CY_ROOT_PATH_SRC_IMO                (0UL)
#define CY_ROOT_PATH_SRC_EXT                (1UL)
#if (SRSS_ECO_PRESENT == 1U)
    #define CY_ROOT_PATH_SRC_ECO            (2UL)
#endif /* (SRSS_ECO_PRESENT == 1U) */
#if defined(SRSS_ALTHF_PRESENT) && (SRSS_ALTHF_PRESENT == 1U)
    #define CY_ROOT_PATH_SRC_ALTHF          (3UL)
#endif /* (SRSS_ALTHF_PRESENT == 1U) */
#define CY_ROOT_PATH_SRC_DSI_MUX            (4UL)
#define CY_ROOT_PATH_SRC_DSI_MUX_HVILO      (16UL)
#define CY_ROOT_PATH_SRC_DSI_MUX_WCO        (17UL)
#if defined(SRSS_ALTHF_PRESENT) && (SRSS_ALTLF_PRESENT == 1U)
    #define CY_ROOT_PATH_SRC_DSI_MUX_ALTLF  (18UL)
#endif /* (SRSS_ALTLF_PRESENT == 1U) */
#if (SRSS_PILO_PRESENT == 1U)
    #define CY_ROOT_PATH_SRC_DSI_MUX_PILO   (19UL)
#endif /* (SRSS_PILO_PRESENT == 1U) */

#define SCB_CPACR_CP10_CP11_ENABLE      (0xFUL << 20U)

/*******************************************************************************
* Function Name: SystemInit
****************************************************************************//**
* \cond
* Initializes the system:
* - Restores FLL registers to the default state for single core devices.
* - Unlocks and disables WDT.
* - Calls the Cy_SystemInit() function.
* - Calls \ref SystemCoreClockUpdate().
* \endcond
*******************************************************************************/
void SystemInit(void)
{
#ifdef CY_DEVICE_FORCE_IP_ENABLE_IN_STARTUP
    /* Release reset for all groups IP except group 0 */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl((uint32_t)PERI_0_GROUP_1, CY_SYSCLK_PERI_GROUP_SL_CTL2, 0x0U); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl((uint32_t)PERI_0_GROUP_2, CY_SYSCLK_PERI_GROUP_SL_CTL2, 0x0U); /* Suppress a compiler warning about unused return value */

    /* release reset of nnlite */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl((uint32_t)PERI_0_GROUP_4, CY_SYSCLK_PERI_GROUP_SL_CTL2, 0x0U); /* Suppress a compiler warning about unused return value */

    (void)Cy_SysClk_PeriGroupSetSlaveCtl((uint32_t)PERI_0_GROUP_1, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFFFFFU); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl((uint32_t)PERI_0_GROUP_2, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFFFFFU); /* Suppress a compiler warning about unused return value */

    /* enable nnlite */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl((uint32_t)PERI_0_GROUP_4, CY_SYSCLK_PERI_GROUP_SL_CTL, 0x1U); /* Suppress a compiler warning about unused return value */

    /* For enabling SYS_MMIO_3, we need CLK_HF11 to be enabled first */
    (void)Cy_SysClk_ClkHfSetSource(11U, CY_SYSCLK_CLKHF_IN_CLKPATH0);  /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_ClkHfSetDivider(11U, CY_SYSCLK_CLKHF_NO_DIVIDE); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_ClkHfEnable(11U);         /* Suppress a compiler warning about unused return value */

    /* enable HF3 and HF4 for SMIF */
    (void)Cy_SysClk_ClkHfSetSource(3U, CY_SYSCLK_CLKHF_IN_CLKPATH0);  /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_ClkHfSetDivider(3U, CY_SYSCLK_CLKHF_NO_DIVIDE); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_ClkHfEnable(3U);         /* Suppress a compiler warning about unused return value */

    (void)Cy_SysClk_ClkHfSetSource(4U, CY_SYSCLK_CLKHF_IN_CLKPATH0);  /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_ClkHfSetDivider(4U, CY_SYSCLK_CLKHF_NO_DIVIDE); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_ClkHfEnable(4U);         /* Suppress a compiler warning about unused return value */

    (void)Cy_SysClk_PeriGroupSetSlaveCtl((uint32_t)PERI_0_GROUP_3, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFFFFFU); /* Suppress a compiler warning about unused return value */
#endif

    Cy_SystemInit();

}

/*******************************************************************************
* Function Name: Cy_SystemInit
****************************************************************************//**
*
* The function is called during device startup.
*
*******************************************************************************/
__WEAK void Cy_SystemInit(void)
{
     /* Empty weak function.
     */
    __NOP(); /* No operation */
}

/*******************************************************************************
* Function Name: SystemCoreClockUpdate
****************************************************************************//**
*
* Gets core clock frequency and updates \ref SystemCoreClock, \ref
* cy_Hfclk0FreqHz, and \ref cy_PeriClkFreqHz.
*
* Updates global variables used by the \ref Cy_SysLib_Delay(), \ref
* Cy_SysLib_DelayUs(), and \ref Cy_SysLib_DelayCycles().
*
*******************************************************************************/
void SystemCoreClockUpdate (void)
{
    uint32_t pathFreqHz;
    uint32_t clkHfPath;

    /* Get frequency for the high-frequency clock # 0 */
    clkHfPath = CY_SYSCLK_CLK_CORE_HF_PATH_NUM;

    pathFreqHz = Cy_SysClk_ClkHfGetFrequency(clkHfPath);

    SystemCoreClock = pathFreqHz;

    cy_Hfclk0FreqHz = SystemCoreClock;

    /* Get frequency for the high-frequency clock # 2 , which is used for PERI PCLK*/
    clkHfPath = CY_SYSCLK_CLK_PERI_HF_PATH_NUM;

    pathFreqHz = Cy_SysClk_ClkHfGetFrequency(clkHfPath);

    cy_PeriClkFreqHz = pathFreqHz;

    /* Sets clock frequency for Delay API */
    cy_delayFreqHz = SystemCoreClock;
    cy_delayFreqMhz = (uint32_t)((cy_delayFreqHz + CY_DELAY_1M_MINUS_1_THRESHOLD) / CY_DELAY_1M_THRESHOLD);
    cy_delayFreqKhz = (cy_delayFreqHz + CY_DELAY_1K_MINUS_1_THRESHOLD) / CY_DELAY_1K_THRESHOLD;

    /* Get the frequency of AHB source, CLK HF0 is the source for AHB*/
    cy_AhbFreqHz = Cy_SysClk_ClkHfGetFrequency(0UL);
}

/* [] END OF FILE */

