/*******************************************************************************
 * File Name: cycfg_system.c
 *
 * Description:
 * System configuration
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

#include "cycfg_system.h"

#define CY_CFG_SYSCLK_ECO_ERROR 1
#define CY_CFG_SYSCLK_ALTHF_ERROR 2
#define CY_CFG_SYSCLK_PLL_ERROR 3
#define CY_CFG_SYSCLK_WCO_ERROR 5
#define CY_CFG_SYSCLK_CLKBAK_ENABLED 1
#define CY_CFG_SYSCLK_CLKBAK_SOURCE CY_SYSCLK_BAK_IN_WCO
#define CY_CFG_SYSCLK_ECO_ENABLED 1
#define CY_CFG_SYSCLK_ECO_FREQ 17203200UL
#define CY_CFG_SYSCLK_ECO_GPIO_IN_PRT GPIO_PRT19
#define CY_CFG_SYSCLK_ECO_GPIO_IN_PIN 0
#define CY_CFG_SYSCLK_ECO_GPIO_OUT_PRT GPIO_PRT19
#define CY_CFG_SYSCLK_ECO_GPIO_OUT_PIN 1
#define CY_CFG_SYSCLK_EXTCLK_ENABLED 1
#define CY_CFG_SYSCLK_EXTCLK_FREQ 24000000UL
#define CY_CFG_SYSCLK_EXTCLK_GPIO_PRT GPIO_PRT7
#define CY_CFG_SYSCLK_EXTCLK_GPIO_PIN 4
#define CY_CFG_SYSCLK_EXTCLK_GPIO_HSIOM P7_4_SRSS_EXT_CLK
#define CY_CFG_SYSCLK_CLKHF0_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF0_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_2
#define CY_CFG_SYSCLK_CLKHF0_FREQ_MHZ 200UL
#define CY_CFG_SYSCLK_CLKHF0_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_CLKHF10_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF10_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_4
#define CY_CFG_SYSCLK_CLKHF10_FREQ_MHZ 100UL
#define CY_CFG_SYSCLK_CLKHF10_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_CLKHF11_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF11_DIVIDER CY_SYSCLK_CLKHF_NO_DIVIDE
#define CY_CFG_SYSCLK_CLKHF11_FREQ_MHZ 199UL
#define CY_CFG_SYSCLK_CLKHF11_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH0
#define CY_CFG_SYSCLK_CLKHF12_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF12_DIVIDER CY_SYSCLK_CLKHF_NO_DIVIDE
#define CY_CFG_SYSCLK_CLKHF12_FREQ_MHZ 24UL
#define CY_CFG_SYSCLK_CLKHF12_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH4
#define CY_CFG_SYSCLK_CLKHF13_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF13_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_4
#define CY_CFG_SYSCLK_CLKHF13_FREQ_MHZ 100UL
#define CY_CFG_SYSCLK_CLKHF13_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_CLKHF1_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF1_DIVIDER CY_SYSCLK_CLKHF_NO_DIVIDE
#define CY_CFG_SYSCLK_CLKHF1_FREQ_MHZ 400UL
#define CY_CFG_SYSCLK_CLKHF1_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_CLKHF2_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF2_DIVIDER CY_SYSCLK_CLKHF_NO_DIVIDE
#define CY_CFG_SYSCLK_CLKHF2_FREQ_MHZ 400UL
#define CY_CFG_SYSCLK_CLKHF2_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_CLKHF3_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF3_DIVIDER CY_SYSCLK_CLKHF_NO_DIVIDE
#define CY_CFG_SYSCLK_CLKHF3_FREQ_MHZ 199UL
#define CY_CFG_SYSCLK_CLKHF3_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH0
#define CY_CFG_SYSCLK_CLKHF4_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF4_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_2
#define CY_CFG_SYSCLK_CLKHF4_FREQ_MHZ 200UL
#define CY_CFG_SYSCLK_CLKHF4_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_CLKHF5_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF5_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_2
#define CY_CFG_SYSCLK_CLKHF5_FREQ_MHZ 200UL
#define CY_CFG_SYSCLK_CLKHF5_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_CLKHF6_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF6_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_2
#define CY_CFG_SYSCLK_CLKHF6_FREQ_MHZ 200UL
#define CY_CFG_SYSCLK_CLKHF6_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_CLKHF7_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF7_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_4
#define CY_CFG_SYSCLK_CLKHF7_FREQ_MHZ 16UL
#define CY_CFG_SYSCLK_CLKHF7_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH1
#define CY_CFG_SYSCLK_CLKHF8_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF8_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_4
#define CY_CFG_SYSCLK_CLKHF8_FREQ_MHZ 50UL
#define CY_CFG_SYSCLK_CLKHF8_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH0
#define CY_CFG_SYSCLK_CLKHF9_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF9_DIVIDER CY_SYSCLK_CLKHF_DIVIDE_BY_5
#define CY_CFG_SYSCLK_CLKHF9_FREQ_MHZ 80UL
#define CY_CFG_SYSCLK_CLKHF9_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH2
#define CY_CFG_SYSCLK_IHO_ENABLED 1
#define CY_CFG_SYSCLK_CLKLF_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH0_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH0_SOURCE CY_SYSCLK_CLKPATH_IN_ECO
#define CY_CFG_SYSCLK_CLKPATH0_SOURCE_NUM 1UL
#define CY_CFG_SYSCLK_CLKPATH1_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH1_SOURCE CY_SYSCLK_CLKPATH_IN_ECO
#define CY_CFG_SYSCLK_CLKPATH1_SOURCE_NUM 1UL
#define CY_CFG_SYSCLK_CLKPATH2_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH2_SOURCE CY_SYSCLK_CLKPATH_IN_IHO
#define CY_CFG_SYSCLK_CLKPATH2_SOURCE_NUM 7UL
#define CY_CFG_SYSCLK_CLKPATH3_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH3_SOURCE CY_SYSCLK_CLKPATH_IN_IHO
#define CY_CFG_SYSCLK_CLKPATH3_SOURCE_NUM 7UL
#define CY_CFG_SYSCLK_CLKPATH4_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH4_SOURCE CY_SYSCLK_CLKPATH_IN_EXT
#define CY_CFG_SYSCLK_CLKPATH4_SOURCE_NUM 2UL
#define CY_CFG_SYSCLK_CLKPATH5_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH5_SOURCE CY_SYSCLK_CLKPATH_IN_IHO
#define CY_CFG_SYSCLK_CLKPATH5_SOURCE_NUM 7UL
#define CY_CFG_SYSCLK_PILO_ENABLED 1
#define CY_CFG_SYSCLK_DPLL_LP0_ENABLED 1
#define CY_CFG_SYSCLK_DPLL_LP0_FEEDBACK_DIV 34
#define CY_CFG_SYSCLK_DPLL_LP0_REFERENCE_DIV 3
#define CY_CFG_SYSCLK_DPLL_LP0_OUTPUT_DIV 1
#define CY_CFG_SYSCLK_DPLL_LP0_FRAC_DIV 14717513
#define CY_CFG_SYSCLK_DPLL_LP0_FRAC_DITHER_EN false
#define CY_CFG_SYSCLK_DPLL_LP0_FRAC_EN true
#define CY_CFG_SYSCLK_DPLL_LP0_LF_MODE false
#define CY_CFG_SYSCLK_DPLL_LP0_OUTPUT_MODE CY_SYSCLK_FLLPLL_OUTPUT_AUTO
#define CY_CFG_SYSCLK_DPLL_LP0_OUTPUT_FREQ 199999999
#define CY_CFG_SYSCLK_DPLL_LP1_ENABLED 1
#define CY_CFG_SYSCLK_DPLL_LP1_FEEDBACK_DIV 34
#define CY_CFG_SYSCLK_DPLL_LP1_REFERENCE_DIV 3
#define CY_CFG_SYSCLK_DPLL_LP1_OUTPUT_DIV 3
#define CY_CFG_SYSCLK_DPLL_LP1_FRAC_DIV 4793490
#define CY_CFG_SYSCLK_DPLL_LP1_FRAC_DITHER_EN false
#define CY_CFG_SYSCLK_DPLL_LP1_FRAC_EN true
#define CY_CFG_SYSCLK_DPLL_LP1_LF_MODE false
#define CY_CFG_SYSCLK_DPLL_LP1_OUTPUT_MODE CY_SYSCLK_FLLPLL_OUTPUT_AUTO
#define CY_CFG_SYSCLK_DPLL_LP1_OUTPUT_FREQ 65535999
#define CY_CFG_SYSCLK_DPLL_HP0_ENABLED 1
#define CY_CFG_SYSCLK_DPLL_HP0_P_DIV 0
#define CY_CFG_SYSCLK_DPLL_HP0_N_DIV 15
#define CY_CFG_SYSCLK_DPLL_HP0_K_DIV 1
#define CY_CFG_SYSCLK_DPLL_HP0_FRAC_DIV 0
#define CY_CFG_SYSCLK_DPLL_HP0_OUTPUT_MODE CY_SYSCLK_FLLPLL_OUTPUT_AUTO
#define CY_CFG_SYSCLK_DPLL_HP0_OUTPUT_FREQ 400000000
#define CY_CFG_SYSCLK_WCO_ENABLED 1
#define CY_CFG_SYSCLK_WCO_IN_PRT GPIO_PRT18
#define CY_CFG_SYSCLK_WCO_IN_PIN 1U
#define CY_CFG_SYSCLK_WCO_OUT_PRT GPIO_PRT18
#define CY_CFG_SYSCLK_WCO_OUT_PIN 0U
#define CY_CFG_SYSCLK_WCO_BYPASS CY_SYSCLK_WCO_NOT_BYPASSED
#define CY_CFG_PWR_ENABLED 1
#define CY_CFG_PWR_INIT 1
#define CY_CFG_PWR_USING_PMIC 0
#define CY_CFG_PWR_VBACKUP_USING_VDDD 1
#define CY_CFG_PWR_REGULATOR_MODE_MIN 0
#define CY_CFG_PWR_USING_ULP 0
#define CY_CFG_PWR_USING_LP 0
#define CY_CFG_PWR_USING_HP 1

#if defined (CY_PDL_TZ_ENABLED)
static const cy_stc_clk_eco_config_t srss_0_clock_0_eco_0_config =
{
    .ecoClkfreq = 17203200U,
    .ecoCtrim = 6U,
    .ecoGtrim = 2U,
    .ecoIboost = 1U,
};
#endif /* defined (CY_PDL_TZ_ENABLED) */

#if defined (CY_USING_HAL)
const cyhal_resource_inst_t srss_0_clock_0_pathmux_0_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 0U,
    .channel_num = 0U,
};
const cyhal_resource_inst_t srss_0_clock_0_pathmux_1_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 1U,
    .channel_num = 0U,
};
const cyhal_resource_inst_t srss_0_clock_0_pathmux_2_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 2U,
    .channel_num = 0U,
};
const cyhal_resource_inst_t srss_0_clock_0_pathmux_3_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 3U,
    .channel_num = 0U,
};
const cyhal_resource_inst_t srss_0_clock_0_pathmux_4_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 4U,
    .channel_num = 0U,
};
const cyhal_resource_inst_t srss_0_clock_0_pathmux_5_obj =
{
    .type = CYHAL_RSC_CLKPATH,
    .block_num = 5U,
    .channel_num = 0U,
};
#endif /* defined (CY_USING_HAL) */

#if defined(CORE_NAME_CM33_0)
static cy_stc_dpll_lp_config_t srss_0_clock_0_pll250m_0_lp_pllConfig =
{
    .feedbackDiv = 34,
    .referenceDiv = 3,
    .outputDiv = 1,
    .pllDcoMode = false,
    .outputMode = CY_SYSCLK_FLLPLL_OUTPUT_AUTO,
    .fracDiv = 14717513,
    .fracDitherEn = false,
    .fracEn = true,
    .dcoCode = 0xFU,
    .kiInt = 0xAU,
    .kiFrac = 0xBU,
    .kiSscg = 0x7U,
    .kpInt = 0x8U,
    .kpFrac = 0x9U,
    .kpSscg = 0x7U,
};
static cy_stc_pll_manual_config_t srss_0_clock_0_pll250m_0_pllConfig =
{
    .lpPllCfg = &srss_0_clock_0_pll250m_0_lp_pllConfig,
};
static cy_stc_dpll_lp_config_t srss_0_clock_0_pll250m_1_lp_pllConfig =
{
    .feedbackDiv = 34,
    .referenceDiv = 3,
    .outputDiv = 3,
    .pllDcoMode = false,
    .outputMode = CY_SYSCLK_FLLPLL_OUTPUT_AUTO,
    .fracDiv = 4793490,
    .fracDitherEn = false,
    .fracEn = true,
    .dcoCode = 0xFU,
    .kiInt = 0xAU,
    .kiFrac = 0xBU,
    .kiSscg = 0x7U,
    .kpInt = 0x8U,
    .kpFrac = 0x9U,
    .kpSscg = 0x7U,
};
static cy_stc_pll_manual_config_t srss_0_clock_0_pll250m_1_pllConfig =
{
    .lpPllCfg = &srss_0_clock_0_pll250m_1_lp_pllConfig,
};
static cy_stc_dpll_hp_config_t srss_0_clock_0_pll500m_0_hp_pllConfig =
{
    .pDiv = 0,
    .nDiv = 15,
    .kDiv = 1,
    .nDivFract = 0,
    .freqModeSel = (cy_en_wait_mode_select_t)7,
    .ivrTrim = 0x8U,
    .clkrSel = 0x1U,
    .alphaCoarse = 0xCU,
    .betaCoarse = 0x5U,
    .flockThresh = 3,
    .flockWait = 0x6U,
    .flockLkThres = 0x7U,
    .flockLkWait = 0x4U,
    .alphaExt = 0x14U,
    .betaExt = 20,
    .lfEn = 0x1U,
    .dcEn = 0x1U,
    .outputMode = CY_SYSCLK_FLLPLL_OUTPUT_AUTO,
};
static cy_stc_pll_manual_config_t srss_0_clock_0_pll500m_0_pllConfig =
{
    .hpPllCfg = &srss_0_clock_0_pll500m_0_hp_pllConfig,
};
#endif /* defined(CORE_NAME_CM33_0) */

__WEAK void cycfg_ClockStartupError(uint32_t error)
{
    (void)error; /* Suppress the compiler warning */
    while(1);
}

#if defined(CORE_NAME_CM33_0)
__STATIC_INLINE void Cy_SysClk_ClkBakInit()
{
    Cy_SysClk_ClkBakSetSource(CY_SYSCLK_BAK_IN_WCO);
}
__STATIC_INLINE void Cy_SysClk_EcoInit()
{
    #if defined (CY_PDL_TZ_ENABLED)
    (void)Cy_GPIO_Pin_FastInit(GPIO_PRT19, 0, CY_GPIO_DM_ANALOG, 0UL, HSIOM_SEL_GPIO);
    (void)Cy_GPIO_Pin_FastInit(GPIO_PRT19, 1, CY_GPIO_DM_ANALOG, 0UL, HSIOM_SEL_GPIO);
    if (CY_SYSCLK_BAD_PARAM == Cy_SysClk_EcoManualConfigure(&srss_0_clock_0_eco_0_config))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_ECO_ERROR);
    }
    if (CY_SYSCLK_TIMEOUT == Cy_SysClk_EcoEnable(3000UL))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_ECO_ERROR);
    }
    #endif
}
#endif /* defined(CORE_NAME_CM33_0) */

#if defined(CORE_NAME_CM33_0) && defined(CY_PDL_TZ_ENABLED)
__STATIC_INLINE void Cy_SysClk_ExtClkInit()
{
    (void)Cy_GPIO_Pin_SecFastInit(GPIO_PRT7, 4, CY_GPIO_DM_HIGHZ, 0UL, P7_4_SRSS_EXT_CLK);
}
#endif /* defined(CORE_NAME_CM33_0) && defined(CY_PDL_TZ_ENABLED) */

#if defined(CORE_NAME_CM33_0)
__STATIC_INLINE void Cy_SysClk_ClkHf0Init()
{
    Cy_SysClk_ClkHfSetDivider(0U, CY_SYSCLK_CLKHF_DIVIDE_BY_2);
    Cy_SysClk_ClkHfSetSource(0U, CY_CFG_SYSCLK_CLKHF0_CLKPATH);
}
__STATIC_INLINE void Cy_SysClk_ClkHf10Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF10, CY_CFG_SYSCLK_CLKHF10_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF10, CY_SYSCLK_CLKHF_DIVIDE_BY_4);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF10);
}
__STATIC_INLINE void Cy_SysClk_ClkHf11Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF11, CY_CFG_SYSCLK_CLKHF11_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF11, CY_SYSCLK_CLKHF_NO_DIVIDE);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF11);
}
__STATIC_INLINE void Cy_SysClk_ClkHf12Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF12, CY_CFG_SYSCLK_CLKHF12_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF12, CY_SYSCLK_CLKHF_NO_DIVIDE);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF12);
}
__STATIC_INLINE void Cy_SysClk_ClkHf13Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF13, CY_CFG_SYSCLK_CLKHF13_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF13, CY_SYSCLK_CLKHF_DIVIDE_BY_4);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF13);
}
__STATIC_INLINE void Cy_SysClk_ClkHf1Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF1, CY_CFG_SYSCLK_CLKHF1_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF1, CY_SYSCLK_CLKHF_NO_DIVIDE);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF1);
}
__STATIC_INLINE void Cy_SysClk_ClkHf2Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF2, CY_CFG_SYSCLK_CLKHF2_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF2, CY_SYSCLK_CLKHF_NO_DIVIDE);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF2);
}
__STATIC_INLINE void Cy_SysClk_ClkHf3Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF3, CY_CFG_SYSCLK_CLKHF3_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF3, CY_SYSCLK_CLKHF_NO_DIVIDE);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF3);
}
__STATIC_INLINE void Cy_SysClk_ClkHf4Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF4, CY_CFG_SYSCLK_CLKHF4_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF4, CY_SYSCLK_CLKHF_DIVIDE_BY_2);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF4);
}
__STATIC_INLINE void Cy_SysClk_ClkHf5Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF5, CY_CFG_SYSCLK_CLKHF5_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF5, CY_SYSCLK_CLKHF_DIVIDE_BY_2);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF5);
}
__STATIC_INLINE void Cy_SysClk_ClkHf6Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF6, CY_CFG_SYSCLK_CLKHF6_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF6, CY_SYSCLK_CLKHF_DIVIDE_BY_2);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF6);
}
__STATIC_INLINE void Cy_SysClk_ClkHf7Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF7, CY_CFG_SYSCLK_CLKHF7_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF7, CY_SYSCLK_CLKHF_DIVIDE_BY_4);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF7);
}
__STATIC_INLINE void Cy_SysClk_ClkHf8Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF8, CY_CFG_SYSCLK_CLKHF8_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF8, CY_SYSCLK_CLKHF_DIVIDE_BY_4);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF8);
}
__STATIC_INLINE void Cy_SysClk_ClkHf9Init()
{
    Cy_SysClk_ClkHfSetSource(CY_CFG_SYSCLK_CLKHF9, CY_CFG_SYSCLK_CLKHF9_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(CY_CFG_SYSCLK_CLKHF9, CY_SYSCLK_CLKHF_DIVIDE_BY_5);
    Cy_SysClk_ClkHfEnable(CY_CFG_SYSCLK_CLKHF9);
}
__STATIC_INLINE void Cy_SysClk_IhoInit()
{
    Cy_SysClk_IhoEnable();
     #ifdef CY_CFG_SYSCLK_IHO_TRIM_VALUE
         Cy_SysClk_IhoSetTrim(CY_CFG_SYSCLK_IHO_TRIM_VALUE);
     #endif /* CY_CFG_SYSCLK_IHO_TRIM_VALUE */
}
__STATIC_INLINE void Cy_SysClk_ClkLfInit()
{
    /* The WDT is unlocked in the default startup code */
    Cy_SysClk_ClkLfSetSource(CY_CFG_SYSCLK_CLKLF_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath0Init()
{
    Cy_SysClk_ClkPathSetSource(0U, CY_CFG_SYSCLK_CLKPATH0_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath1Init()
{
    Cy_SysClk_ClkPathSetSource(1U, CY_CFG_SYSCLK_CLKPATH1_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath2Init()
{
    Cy_SysClk_ClkPathSetSource(2U, CY_CFG_SYSCLK_CLKPATH2_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath3Init()
{
    Cy_SysClk_ClkPathSetSource(3U, CY_CFG_SYSCLK_CLKPATH3_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath4Init()
{
    Cy_SysClk_ClkPathSetSource(4U, CY_CFG_SYSCLK_CLKPATH4_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath5Init()
{
    Cy_SysClk_ClkPathSetSource(5U, CY_CFG_SYSCLK_CLKPATH5_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_PiloInit()
{
    Cy_SysClk_PiloEnable();
}
__STATIC_INLINE void Cy_SysClk_Dpll_Lp0_Init()
{
    uint32_t clkHfMask = 0;

    #if !defined (CY_PDL_TZ_ENABLED)
    if (Cy_SysClk_PllIsEnabled(SRSS_DPLL_LP_0_PATH_NUM))
        return;

    #endif
    Cy_SysClk_PllDisable(SRSS_DPLL_LP_0_PATH_NUM);

    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllManualConfigure(SRSS_DPLL_LP_0_PATH_NUM, &srss_0_clock_0_pll250m_0_pllConfig))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
    clkHfMask = Cy_SysClk_ClkHfGetMaskOnPath((cy_en_clkhf_in_sources_t)SRSS_DPLL_LP_0_PATH_NUM);
    if(clkHfMask)
    {
        Cy_SysClk_ClkHfEnableDirectMuxWithMask(clkHfMask, true);
    }
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllEnable(SRSS_DPLL_LP_0_PATH_NUM, 10000u))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
    else
    {
        Cy_SysLib_DelayUs(SRSS_DPLL_LP_INIT_DELAY_USEC);
        Cy_SysClk_ClkHfEnableDirectMuxWithMask(clkHfMask, false);
    }
}
__STATIC_INLINE void Cy_SysClk_Dpll_Lp1_Init()
{
    uint32_t clkHfMask = 0;

    #if !defined (CY_PDL_TZ_ENABLED)
    if (Cy_SysClk_PllIsEnabled(SRSS_DPLL_LP_1_PATH_NUM))
        return;

    #endif
    Cy_SysClk_PllDisable(SRSS_DPLL_LP_1_PATH_NUM);

    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllManualConfigure(SRSS_DPLL_LP_1_PATH_NUM, &srss_0_clock_0_pll250m_1_pllConfig))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
    clkHfMask = Cy_SysClk_ClkHfGetMaskOnPath((cy_en_clkhf_in_sources_t)SRSS_DPLL_LP_1_PATH_NUM);
    if(clkHfMask)
    {
        Cy_SysClk_ClkHfEnableDirectMuxWithMask(clkHfMask, true);
    }
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllEnable(SRSS_DPLL_LP_1_PATH_NUM, 10000u))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
    else
    {
        Cy_SysLib_DelayUs(SRSS_DPLL_LP_INIT_DELAY_USEC);
        Cy_SysClk_ClkHfEnableDirectMuxWithMask(clkHfMask, false);
    }
}
__STATIC_INLINE void Cy_SysClk_Dpll_Hp0_Init()
{
    #if !defined (CY_PDL_TZ_ENABLED)
    if (Cy_SysClk_PllIsEnabled(SRSS_DPLL_HP_0_PATH_NUM))
        return;

    #endif
    Cy_SysClk_PllDisable(SRSS_DPLL_HP_0_PATH_NUM);

    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllManualConfigure(SRSS_DPLL_HP_0_PATH_NUM, &srss_0_clock_0_pll500m_0_pllConfig))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_PllEnable(SRSS_DPLL_HP_0_PATH_NUM, 10000u))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_PLL_ERROR);
    }
}
__STATIC_INLINE void Cy_SysClk_WcoInit()
{
    (void)Cy_GPIO_Pin_FastInit(GPIO_PRT18, 1U, 0x00U, 0x00U, HSIOM_SEL_GPIO);
    (void)Cy_GPIO_Pin_FastInit(GPIO_PRT18, 0U, 0x00U, 0x00U, HSIOM_SEL_GPIO);
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_WcoEnable(1000000UL))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_WCO_ERROR);
    }
}
#endif /* defined(CORE_NAME_CM33_0) */

__STATIC_INLINE void init_cycfg_power(void)
{
    Cy_SysPm_Init();
    /* **Reset the Backup domain on POR, XRES, BOD only if Backup domain is supplied by VDDD** */
    #if (CY_CFG_PWR_VBACKUP_USING_VDDD)
         if (0u == Cy_SysLib_GetResetReason() /* POR, XRES, or BOD */)
            {
                Cy_SysLib_ResetBackupDomain();
            }
    #endif /* CY_CFG_PWR_VBACKUP_USING_VDDD */

    /* **System Active Power Mode Profile Configuration** */
    #if (CY_CFG_PWR_SYS_ACTIVE_PROFILE == CY_CFG_PWR_MODE_HP)
        Cy_SysPm_SystemEnterHp();
    #elif (CY_CFG_PWR_SYS_ACTIVE_PROFILE == CY_CFG_PWR_MODE_ULP)
        Cy_SysPm_SystemEnterUlp();
    #elif (CY_CFG_PWR_SYS_ACTIVE_PROFILE == CY_CFG_PWR_MODE_LP)
        Cy_SysPm_SystemEnterLp();
    #endif /* CY_CFG_PWR_SYS_IDLE_MODE */        /* **System Regulators Low Current Configuration** */
    #if (CY_CFG_PWR_REGULATOR_MODE_MIN)
        Cy_SysPm_SystemSetMinRegulatorCurrent();
    #endif /* CY_CFG_PWR_REGULATOR_MODE_MIN */

    /* **System Domain Idle Power Mode Configuration** */
    #if (CY_CFG_PWR_SYS_IDLE_MODE == CY_CFG_PWR_MODE_DEEPSLEEP)
        Cy_SysPm_SetDeepSleepMode(CY_SYSPM_MODE_DEEPSLEEP);
    #elif (CY_CFG_PWR_SYS_IDLE_MODE == CY_CFG_PWR_MODE_DEEPSLEEP_RAM)
        Cy_SysPm_SetDeepSleepMode(CY_SYSPM_MODE_DEEPSLEEP_RAM);
    #elif (CY_CFG_PWR_SYS_IDLE_MODE == CY_CFG_PWR_MODE_DEEPSLEEP_OFF)
        Cy_SysPm_SetDeepSleepMode(CY_SYSPM_MODE_DEEPSLEEP_OFF);
    #endif /* CY_CFG_PWR_SYS_IDLE_MODE */
}
void init_cycfg_system(void)
{
    #if defined(CORE_NAME_CM33_0)
    /* Enable all source clocks */
    #ifdef CY_CFG_SYSCLK_IHO_ENABLED
        Cy_SysClk_IhoInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_PILO_ENABLED
        Cy_SysClk_PiloInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_WCO_ENABLED
        Cy_SysClk_WcoInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_ECO_ENABLED
        Cy_SysClk_EcoInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_CLKLF_ENABLED
        Cy_SysClk_ClkLfInit();
    #endif
    
    #ifdef CY_PDL_TZ_ENABLED
    #ifdef CY_CFG_SYSCLK_EXTCLK_ENABLED
        Cy_SysClk_ExtClkInit();
    #endif
    #endif
    
    #ifdef CY_CFG_SYSCLK_ALTHF_ENABLED
        Cy_SysClk_AltHfInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_CLKPERI_ENABLED
        Cy_SysClk_ClkPeriInit();
    #endif
    
    #ifdef CY_PDL_TZ_ENABLED
        Cy_SysClk_PllDisable(SRSS_DPLL_HP_0_PATH_NUM);
        Cy_SysClk_PllDisable(SRSS_DPLL_LP_0_PATH_NUM);
        Cy_SysClk_PllDisable(SRSS_DPLL_LP_1_PATH_NUM);
    #endif
    /* Configure Path Clocks */
    #ifdef CY_CFG_SYSCLK_CLKPATH1_ENABLED
        Cy_SysClk_ClkPath1Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH2_ENABLED
        Cy_SysClk_ClkPath2Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH3_ENABLED
        Cy_SysClk_ClkPath3Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH4_ENABLED
        Cy_SysClk_ClkPath4Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH5_ENABLED
        Cy_SysClk_ClkPath5Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH6_ENABLED
        Cy_SysClk_ClkPath6Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH7_ENABLED
        Cy_SysClk_ClkPath7Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH8_ENABLED
        Cy_SysClk_ClkPath8Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH9_ENABLED
        Cy_SysClk_ClkPath9Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH10_ENABLED
        Cy_SysClk_ClkPath10Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH11_ENABLED
        Cy_SysClk_ClkPath11Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH12_ENABLED
        Cy_SysClk_ClkPath12Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH13_ENABLED
        Cy_SysClk_ClkPath13Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH14_ENABLED
        Cy_SysClk_ClkPath14Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKPATH15_ENABLED
        Cy_SysClk_ClkPath15Init();
    #endif
    
    /* Configure and enable PLLs */
    #ifdef CY_CFG_SYSCLK_DPLL_HP0_ENABLED
        Cy_SysClk_Dpll_Hp0_Init();
    #endif
    /* Configure HF clocks */
    #ifdef CY_CFG_SYSCLK_CLKHF1_ENABLED
        Cy_SysClk_ClkHf1Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF2_ENABLED
        Cy_SysClk_ClkHf2Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF3_ENABLED
        Cy_SysClk_ClkHf3Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF4_ENABLED
        Cy_SysClk_ClkHf4Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF5_ENABLED
        Cy_SysClk_ClkHf5Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF6_ENABLED
        Cy_SysClk_ClkHf6Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF7_ENABLED
        Cy_SysClk_ClkHf7Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF8_ENABLED
        Cy_SysClk_ClkHf8Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF9_ENABLED
        Cy_SysClk_ClkHf9Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF10_ENABLED
        Cy_SysClk_ClkHf10Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF11_ENABLED
        Cy_SysClk_ClkHf11Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF12_ENABLED
        Cy_SysClk_ClkHf12Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF13_ENABLED
        Cy_SysClk_ClkHf13Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF14_ENABLED
        Cy_SysClk_ClkHf14Init();
    #endif
    #ifdef CY_CFG_SYSCLK_CLKHF15_ENABLED
        Cy_SysClk_ClkHf15Init();
    #endif
    
    #ifdef CY_CFG_SYSCLK_CLKALTSYSTICK_ENABLED
        Cy_SysClk_ClkAltSysTickInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_CLKPUMP_ENABLED
        Cy_SysClk_ClkPumpInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_CLKBAK_ENABLED
        Cy_SysClk_ClkBakInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_MFO_ENABLED
        Cy_SysClk_MfoInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_CLKMF_ENABLED
        Cy_SysClk_ClkMfInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_CLKPWR_ENABLED
        Cy_SysClk_ClkPwrInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_CLKPATH0_ENABLED
        Cy_SysClk_ClkPath0Init();
    #endif
    /* Configure and enable DPLLs */
    #ifdef CY_CFG_SYSCLK_DPLL_LP0_ENABLED
        Cy_SysClk_Dpll_Lp0_Init();
    #endif
    #ifdef CY_CFG_SYSCLK_DPLL_LP1_ENABLED
        Cy_SysClk_Dpll_Lp1_Init();
    #endif
    
    Cy_SysClk_ClkHf0Init();
    
    #ifdef CY_CFG_SYSCLK_CLKFAST_0_ENABLED
        Cy_SysClk_ClkFast_0_Init();
    #endif
    
    #ifdef CY_CFG_SYSCLK_CLKFAST_1_ENABLED
        Cy_SysClk_ClkFast_1_Init();
    #endif
    
    #ifdef CY_CFG_SYSCLK_CLKSLOW_ENABLED
        Cy_SysClk_ClkSlowInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_CLKMEM_ENABLED
        Cy_SysClk_ClkMemInit();
    #endif
    
#if defined(CY_CFG_SYSCLK_ECO_PRESCALER_ENABLED)
        Cy_SysClk_EcoPrescalerInit();
#endif /* defined(CY_CFG_SYSCLK_ECO_PRESCALER_ENABLED) */
    #endif /* defined(CORE_NAME_CM33_0) */
    #ifdef CY_CFG_SYSCLK_CLKALTSYSTICK_ENABLED
        Cy_SysClk_ClkAltSysTickInit();
    #endif
    
    #ifdef CY_CFG_SYSCLK_ECO_ENABLED
        Cy_SysClk_EcoSetFrequency(CY_CFG_SYSCLK_ECO_FREQ);
    #endif
    
    #ifdef CY_CFG_SYSCLK_EXTCLK_ENABLED
        Cy_SysClk_ExtClkSetFrequency(CY_CFG_SYSCLK_EXTCLK_FREQ);
    #endif
    
    /* Update System Core Clock values for correct Cy_SysLib_Delay functioning */
    SystemCoreClockUpdate();
    #ifdef CY_CFG_PWR_ENABLED
        #ifdef CY_CFG_PWR_INIT
            init_cycfg_power();
        #else
            #warning Power system will not be configured. Update power personality to v1.20 or later.
        #endif /* CY_CFG_PWR_INIT */
    #endif /* CY_CFG_PWR_ENABLED */
    
#if defined (CY_USING_HAL)
    if(CY_RSLT_SUCCESS != (cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_0_obj)))
    {
        CY_HALT();
    }
    if(CY_RSLT_SUCCESS != (cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_1_obj)))
    {
        CY_HALT();
    }
    if(CY_RSLT_SUCCESS != (cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_2_obj)))
    {
        CY_HALT();
    }
    if(CY_RSLT_SUCCESS != (cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_3_obj)))
    {
        CY_HALT();
    }
    if(CY_RSLT_SUCCESS != (cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_4_obj)))
    {
        CY_HALT();
    }
    if(CY_RSLT_SUCCESS != (cyhal_hwmgr_reserve(&srss_0_clock_0_pathmux_5_obj)))
    {
        CY_HALT();
    }
#endif /* defined (CY_USING_HAL) */
}
