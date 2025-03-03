
/***************************************************************************//**
* \file system_cat1d.c
*
* \brief
* The device common system-source file.
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
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
#include "cy_device_headers.h"
#include "cmsis_compiler.h"
#include "cy_syslib.h"
#include "cy_syspm.h"
#include "cy_sysclk.h"
#include "cy_syspm_pdcm.h"
#include "cy_syspm_ppu.h"
#include "cy_secure_services.h"
#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_system_config_system_macro_1d
* \{
*/

#define CY_SYS_CORE_PWR_CTL_KEY_OPEN            (0x05FAUL)  /**< Power Control Key Open */
#define CY_SYS_CORE_PWR_CTL_KEY_CLOSE           (0xFA05UL)  /**< Power Control Key Close */

/** \} group_system_config_system_macro_1d */

#define CY_SYS_CORE_VECTOR_TABLE_VALID_ADDR     (0x0003FFUL)  /**< Valid Vector Table Address*/

#define CY_SYS_CORE_WAIT_10US                   (10U)

#define CY_SYS_CM55_IN_RESET                    (0x1U)
#define CY_SYS_CM55_NOT_IN_RESET                (0x0U)
#define CY_SYS_CM33_IN_RESET                    (0x0U)
#define CY_SYS_CM33_NOT_IN_RESET                (0x1U)

#define CM55_0_CPU_EVENT                        (0xFU)
#define CM33_0_CPU_EVENT                        (0xFU)

#define CY_SYS_CPU_WAIT_DEFAULT                 (0x1U)

#define CY_SYS_SOCMEM_HF_NUM                    (2U)
#define CY_SYS_SOCMEM_PERI_GROUP_ENABLE_OFFSET  (0x2U)

#if (CY_SYSTEM_CPU_M55 == 1UL) || defined(CY_DOXYGEN)
#define CY_SYS_U55_PERI_GROUP_HF_NUM            (1U)
#define CY_SYS_U55_PERI_GROUP_ENABLE_MASK       (0x1U)

/*******************************************************************************
* Function Name: Cy_SysEnableU55
****************************************************************************//**
*
* This function enables or disable U55 ML accelerator based on parameter value.
* In Enable case function will enable clock, PPU and SCTL register.
* In Disable case it will disable PPU and SCTL, clock will not be disabled.
*
* \param enable
* Enable or disable U55
*
*******************************************************************************/
void Cy_SysEnableU55(bool enable)
{
    if(enable)
    {
        /* Enable U55 SCTL */
         Cy_SysClk_PeriGroupSlaveInit(CY_MMIO_MXU550_PERI_NR, CY_MMIO_MXU550_GROUP_NR, CY_MMIO_MXU550_SLAVE_NR, CY_MMIO_MXU550_CLK_HF_NR);
        /* enable U55 PPC */
        cy_pd_ppu_set_power_mode((struct ppu_v1_reg *)CY_PPU_U55_BASE, PPU_V1_MODE_ON);
    }
    else
    {
        cy_pd_ppu_set_power_mode((struct ppu_v1_reg *)CY_PPU_U55_BASE, PPU_V1_MODE_OFF);
        Cy_SysClk_PeriGroupSlaveDeinit(CY_MMIO_MXU550_PERI_NR, CY_MMIO_MXU550_GROUP_NR, CY_MMIO_MXU550_SLAVE_NR);
    }
}
#endif /* (CY_SYSTEM_CPU_M55 == 1UL) || defined(CY_DOXYGEN) */

#if (CY_SYSTEM_CPU_M33 == 1UL) || defined(CY_DOXYGEN)

#define CY_PD1_CLKHF_NUM                    (1U)
#define CY_PD1_PWR_UP_US                    (20U)
#define CY_APPSS_PWR_UP_US                  (12U)
#define CY_SOCMEM_PWR_UP_US                 (12U)
#define CY_PWRMODE_CLK_SEL_DEFAULT_VALUE    (0X00000004U)

/*******************************************************************************
* Function Name: Cy_System_EnablePD1
****************************************************************************//**
*
* Safely Enables the PD1 Power Domain
*
* This function implements the sequence required to safely enable PD1 power
* domain, which includes
*
* - Enabling the required CLK_HF's
*
* - Enabling/Disabling the required Power Domain Dependencies
*
* - Configuring the Power Domain PPU's with appropriate configuration
*
* - Making sure the PD's are properly enabled using the required delay's
*
* As an illustration on when to call this function , refer to below
* PDCM(Power Dependency Control Matrix)...
*
* ![](PSE84_PDCM_Default.png)
*
* Where the table indicates the default PDCM dependencies.
*
* With respect to PD1, table indicates below constraints
*
* 1) If APPCPU, SOCMEM and U55 are ON then APPSS needs to be ON.
*
* 2) If APPSS is ON then PD1 needs to be ON.
*
* If any of the APPCPU, SOCMEM, U55 and APPSS power domains need to be switched
* ON, user needs to call this API first to switch ON PD1 safely.
*
* \note
*
* - Enabling peripherals in SYS_MMIO groups i.e. PERI0 group requires PD0 power domain to be
* ON.
*
* - Enabling peripherals in APP_MMIO groups i.e. PERI1 group requires PD1 power domain to be
* ON.
*
* Once PD1 is enabled, switching ON/OFF of individual power domains under PD1
* can be done using below API's
*
* \ref Cy_SysEnableSOCMEM
*
* \ref Cy_SysEnableCM55
*
* \ref Cy_SysEnableU55
*
*******************************************************************************/
void Cy_System_EnablePD1(void)
{
    uint32_t timeoutUs = CY_PD1_PWR_UP_US;

    /* Sequence based on CDT_005513-163 */

    /* Enable HF1 */
    if(false == Cy_SysClk_ClkHfIsEnabled(CY_PD1_CLKHF_NUM))
    {
        (void)Cy_SysClk_ClkHfEnable(CY_PD1_CLKHF_NUM);         /* Suppress a compiler warning about unused return value */
    }

    /* Configure CLK_SELECT CLK_PWR_DIV to reset value of 4 (to ensure IHO/5), CLK_PWR_MUX to 0 to select IHO as source.*/
    CY_PWRMODE_CLK_SELECT = CY_PWRMODE_CLK_SEL_DEFAULT_VALUE;

    /* Enable PD1 dynamic transitions */
    cy_pd_ppu_enable_dynamic_mode((struct ppu_v1_reg *)CY_PPU_PD1_BASE, true);

    /* 4.Set dependency between SYSTEM and APPCPUSS */
    (void)cy_pd_pdcm_set_dependency(CY_PD_PDCM_APPCPUSS, CY_PD_PDCM_SYSCPU);

    /* Give wait for up to PD1_PWR_UP_US timeout while polling PD1_PPU_MAIN->PWSR_PWR_POLICY == 0x8 */
    for (; (cy_pd_ppu_get_power_mode((struct ppu_v1_reg *)CY_PPU_PD1_BASE) != PPU_V1_MODE_ON ) &&
           (0UL != timeoutUs);
         timeoutUs--)
    {
        Cy_SysLib_DelayUs(1U);
    }

    CY_ASSERT(timeoutUs != 0);

    /* Wait for APPSS_PWR_UP_US (12us?, this is the time to wait on APPCPUSS to exit quiescence state before accessing the APPCPUSS registers */
    Cy_SysLib_DelayUs(CY_APPSS_PWR_UP_US);

    /* Give wait for up to 1us timeout while polling APPCPUSS->PWSR_PWR_POLICY == 0x8 */
    timeoutUs = CY_APPSS_PWR_UP_US;
    for (; (cy_pd_ppu_get_power_mode((struct ppu_v1_reg *)CY_PPU_APPCPUSS_BASE) != PPU_V1_MODE_ON ) &&
           (0UL != timeoutUs);
         timeoutUs--)
    {
        Cy_SysLib_DelayUs(1U);
    }

    CY_ASSERT(timeoutUs != 0);

    /* Enable APPCPUSS dynamic transitions.*/
    cy_pd_ppu_enable_dynamic_mode((struct ppu_v1_reg *)CY_PPU_APPCPUSS_BASE, true);

    /* Unfreeze IO Pins */
    SRSS_PWR_CTL2 |= SRSS_PWR_CTL2_FREEZE_DPSLP_PD1_Msk;
}

/*******************************************************************************
* Function Name: Cy_System_DisablePD1
****************************************************************************//**
*
* Safely Disables the PD1 Power Domain
*
*******************************************************************************/
void Cy_System_DisablePD1(void)
{
    (void)cy_pd_ppu_set_power_mode((struct ppu_v1_reg *)CY_PPU_PD1_BASE, (uint32_t)PPU_V1_MODE_OFF); /* Suppress a compiler warning about unused return value */
    (void)cy_pd_ppu_set_power_mode((struct ppu_v1_reg *)CY_PPU_APPCPUSS_BASE, (uint32_t)PPU_V1_MODE_OFF); /* Suppress a compiler warning about unused return value */
    (void)cy_pd_ppu_set_power_mode((struct ppu_v1_reg *)CY_PPU_SOCMEM_BASE, (uint32_t)PPU_V1_MODE_OFF); /* Suppress a compiler warning about unused return value */

    (void)cy_pd_pdcm_clear_dependency(CY_PD_PDCM_APPCPUSS, CY_PD_PDCM_SYSCPU);
}

/*******************************************************************************
* Function Name: Cy_SysGetCM55Status
****************************************************************************//**
*
* Returns the Cortex-M55 core power mode.
*
* \return \ref group_system_config_core_status_macro_1d
*
*******************************************************************************/
uint32_t Cy_SysGetCM55Status(void)
{
    /* Return current power mode */
    return (MXCM55->CM55_STATUS);
}


/*******************************************************************************
* Function Name: Cy_SysEnableSOCMEM
****************************************************************************//**
*
* Enables SOCMEM IP
*
*******************************************************************************/
void Cy_SysEnableSOCMEM(bool enable)
{
    uint32_t timeoutUs = CY_SOCMEM_PWR_UP_US;

    if(enable)
    {
        /* Enable HF2 for SOCMEM */
        if(false == Cy_SysClk_ClkHfIsEnabled(CY_SYS_SOCMEM_HF_NUM))
        {
            (void)Cy_SysClk_ClkHfEnable(CY_SYS_SOCMEM_HF_NUM);         /* Suppress a compiler warning about unused return value */
        }
        /* Enable SOCMEM dependency on SYSCPU */
        (void)cy_pd_pdcm_set_dependency(CY_PD_PDCM_SOCMEM, CY_PD_PDCM_SYSCPU);
        /* Enable SOCMEM SCTL */
        if(!Cy_SysClk_IsPeriGroupSlaveEnabled(CY_MMIO_SOCMEM_PERI_NR, CY_MMIO_SOCMEM_GROUP_NR, CY_MMIO_SOCMEM_SLAVE_NR))
        {
            Cy_SysClk_PeriGroupSlaveInit(CY_MMIO_SOCMEM_PERI_NR, CY_MMIO_SOCMEM_GROUP_NR, CY_MMIO_SOCMEM_SLAVE_NR, CY_MMIO_SOCMEM_CLK_HF_NR);
        }

        SOCMEM->GK_CTL = SOCMEM_GK_STATUS_OPEN_Msk;

        for (; (cy_pd_ppu_get_power_mode((struct ppu_v1_reg *)CY_PPU_SOCMEM_BASE) != PPU_V1_MODE_ON ) &&
               (0UL != timeoutUs);
             timeoutUs--)
        {
            Cy_SysLib_DelayUs(1U);
        }

        CY_ASSERT(timeoutUs != 0);

    }
    else
    {
        /* Remove SOCMEM dependency on SYSCPU */
        (void)cy_pd_pdcm_clear_dependency(CY_PD_PDCM_SOCMEM, CY_PD_PDCM_SYSCPU);
        Cy_SysClk_PeriGroupSlaveDeinit(CY_MMIO_SOCMEM_PERI_NR, CY_MMIO_SOCMEM_GROUP_NR, CY_MMIO_SOCMEM_SLAVE_NR);
    }
}
/*******************************************************************************
* Function Name: Cy_System_SetCM55DbgPort
****************************************************************************//**
*
* Set APPCPU debug port mode policy
*
* \param dbgMode debug port policy
*
*******************************************************************************/
void Cy_System_SetCM55DbgPort(cy_app_cpu_dbg_port_type_t dbgMode)
{
#if defined(NO_RPC_CALL) || defined (COMPONENT_SECURE_DEVICE)
    switch (dbgMode)
    {
      /** Disable debug port for CM55 */
      case APPCPUSS_DBG_DISABLE:
        APPCPUSS->AP_CTL &= ~(APPCPUSS_AP_CTL_CM55_0_ENABLE_Msk | APPCPUSS_AP_CTL_CM55_0_DBG_ENABLE_Msk |
                APPCPUSS_AP_CTL_CM55_0_NID_ENABLE_Msk);
      break;
      /** Enables invasive debug CM55 */
      case APPCPUSS_DBG_INVASSIVE_MODE:
              APPCPUSS->AP_CTL &= ~(APPCPUSS_AP_CTL_CM55_0_NID_ENABLE_Msk);
              APPCPUSS->AP_CTL |= (APPCPUSS_AP_CTL_CM55_0_ENABLE_Msk | APPCPUSS_AP_CTL_CM55_0_DBG_ENABLE_Msk);
      break;
      /** Enables all trace and non-invasive debug features */
      case APPCPUSS_DBG_TRACES_NON_INVASSIVE_MODE:
        APPCPUSS->AP_CTL &= ~(APPCPUSS_AP_CTL_CM55_0_DBG_ENABLE_Msk);
                    APPCPUSS->AP_CTL |= (APPCPUSS_AP_CTL_CM55_0_ENABLE_Msk | APPCPUSS_AP_CTL_CM55_0_NID_ENABLE_Msk);
      break;
      /** Enables invasive debug & all trace and non-invasive enable for CM55 */
      case APPCPUSS_DBG_ENABLE_ALL:
        APPCPUSS->AP_CTL |= (APPCPUSS_AP_CTL_CM55_0_ENABLE_Msk | APPCPUSS_AP_CTL_CM55_0_DBG_ENABLE_Msk |
                APPCPUSS_AP_CTL_CM55_0_NID_ENABLE_Msk);
      break;
      /** Invalid value passed */
      default:
      break;
    }
#else
    cy_rpc_args_t rpcArgs;
    uint32_t rpcRetVal;
    rpcArgs.argc = 1;
    rpcArgs.argv[0] = (uint32_t)dbgMode;
    Cy_SecureServices_RPC(CY_SECURE_SERVICE_TYPE_SYSTEM,
                      (uint32_t)CY_SECURE_SERVICE_SYS_SET_APPCPU_DBG_MODE, &rpcArgs, &rpcRetVal);

#endif
}

/*******************************************************************************
* Function Name: Cy_SysDisableCM55
****************************************************************************//**
*
* Disables CM55
*
* \note Below is the sequence that needs to be followed
* - Turn OFF the APPCPU PPU.
* - Enter DS on CM55.
*
*******************************************************************************/
void Cy_SysDisableCM55(void)
{
    /* Power OFF the APPCPU Power Domain */
    (void)cy_pd_ppu_set_power_mode((struct ppu_v1_reg *)CY_PPU_APPCPU_BASE, (uint32_t)PPU_V1_MODE_OFF); /* Suppress a compiler warning about unused return value */
}

/*******************************************************************************
* Function Name: Cy_SysEnableCM55
****************************************************************************//**
*
* Sets vector table base address and enables the Cortex-M55 core.
*
* \note If the CPU is already enabled, it is reset and then enabled.
*
* \param vectorTableOffset The offset of the vector table base address from
* memory address 0x00000000. The offset should be multiple to 1024 bytes.
* \param waitus The timeout value in microsecond used to wait for core to be
* booted. value zero is for infinite wait till the core is booted successfully.
*
*******************************************************************************/

void Cy_SysEnableCM55(uint32_t vectorTableOffset, uint32_t waitus)
{
    uint32_t interruptState;
    uint32_t cpuState;
    uint32_t regValue;

    /** TODO: check valid vector address */
    CY_ASSERT_L2((vectorTableOffset & CY_SYS_CORE_VECTOR_TABLE_VALID_ADDR) == 0UL);

    interruptState = Cy_SysLib_EnterCriticalSection();

    cy_pd_pdcm_set_dependency(CY_PD_PDCM_SYSCPU, CY_PD_PDCM_APPCPU);

    /* Power ON the APPCPU Power Domain */
    (void)cy_pd_ppu_set_power_mode((struct ppu_v1_reg *)CY_PPU_APPCPU_BASE, (uint32_t)PPU_V1_MODE_ON); /* Suppress a compiler warning about unused return value */

    /* CDT-393489 to check how can we power on/off core.
       Here we need to power-on the core if it is already in off state. */
    cpuState = Cy_SysGetCM55Status();
    if (CY_SYS_CORE_STATUS_ACTIVE == cpuState)
    {
        Cy_SysResetCM55(CY_SYS_CORE_WAIT_10US);
    }

    MXCM55->CM55_NS_VECTOR_TABLE_BASE = vectorTableOffset;

    /* Reset the core after setting the vector table base address */
    regValue = MXCM55->CM55_CMD & ~(MXCM55_CM55_CMD_RESET_Msk | MXCM55_CM55_CMD_VECTKEYSTAT_Msk);
    regValue |= _VAL2FLD(MXCM55_CM55_CMD_VECTKEYSTAT, CY_SYS_CORE_PWR_CTL_KEY_OPEN); /* set key bits */
    regValue |= _VAL2FLD(MXCM55_CM55_CMD_RESET, CY_SYS_CM55_IN_RESET); /* set reset bit */
    MXCM55->CM55_CMD = regValue;

    if (waitus == CY_SYS_CORE_WAIT_INFINITE)
    {
        while(Cy_SysGetCM55Status() != CY_SYS_CORE_STATUS_ACTIVE)
        {
            /* Wait for the power mode to take effect */
        }
    }
    else
    {
        if(Cy_SysGetCM55Status() != CY_SYS_CORE_STATUS_ACTIVE)
        {
            Cy_SysLib_DelayUs((uint16_t)waitus);
        }
    }

    /* Release CPU wait */
    MXCM55->CM55_CTL &= ~(_VAL2FLD(MXCM55_CM55_CTL_CPU_WAIT, CY_SYS_CPU_WAIT_DEFAULT));

    /* Enable Event from CM33 */
    MXCM55->CM55_EVENT_CTL = CM33_0_CPU_EVENT;

    Cy_SysLib_ExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Cy_SysResetCM55
****************************************************************************//**
*
* Resets the Cortex-M55 core and waits for the mode to take the effect.
*
* \param waitus The timeout value in microsecond used to wait for core to be
* reset. value zero is for infinite wait till the core is reset successfully.
*
* \warning Do not call the function while the Cortex-M55 is executing because
* such a call may corrupt/abort a pending bus-transaction by the CPU and cause
* unexpected behavior in the system including a deadlock. Call the function
* while the Cortex-M55 core is in the Sleep or Deep Sleep low-power mode. Use
* the \ref group_syspm Power Management (syspm) API to put the CPU into the
* low-power modes. Use the \ref Cy_SysPm_ReadStatus() to get a status of the CPU.
*
*******************************************************************************/
void Cy_SysResetCM55(uint32_t waitus)
{
    uint32_t interruptState;
    uint32_t regValue;

    interruptState = Cy_SysLib_EnterCriticalSection();

    regValue = MXCM55->CM55_CMD & ~(MXCM55_CM55_CMD_RESET_Msk | MXCM55_CM55_CMD_VECTKEYSTAT_Msk);
    regValue |= _VAL2FLD(MXCM55_CM55_CMD_VECTKEYSTAT, CY_SYS_CORE_PWR_CTL_KEY_OPEN); /* set key bits */
    regValue |= _VAL2FLD(MXCM55_CM55_CMD_RESET, CY_SYS_CM55_IN_RESET); /* set reset bit */
    MXCM55->CM55_CMD = regValue;

    if (waitus == CY_SYS_CORE_WAIT_INFINITE)
    {
        /* HW automatically clears this field to '0'. This effectively results in a CM55 reset */
        while( _FLD2VAL(MXCM55_CM55_CMD_RESET, MXCM55->CM55_CMD) != CY_SYS_CM55_NOT_IN_RESET)
        {
            /* Wait for the power mode to take effect */
        }
    }
    else
    {
        if( _FLD2VAL(MXCM55_CM55_CMD_RESET, MXCM55->CM55_CMD) != CY_SYS_CM55_NOT_IN_RESET)
        {
            Cy_SysLib_DelayUs((uint16_t)waitus);
        }
    }

    Cy_SysLib_ExitCriticalSection(interruptState);
}

#endif /* (CY_SYSTEM_CPU_M33 == 1UL) || defined(CY_DOXYGEN) */


#if (CY_SYSTEM_CPU_M0P == 1UL) || defined(CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysGetCM33Status
****************************************************************************//**
*
* Returns the Cortex-M33 core power mode.
*
* \return \ref group_system_config_core_status_macro_1d
*
*******************************************************************************/
uint32_t Cy_SysGetCM33Status(void)
{
    /* Return current power mode */
    return (MXCM33->CM33_STATUS);
}


/*******************************************************************************
* Function Name: Cy_SysEnableCM33
****************************************************************************//**
*
* Sets vector table base address and enables the Cortex-M33 core in secure mode.
*
* \note If the CPU is already enabled, it is reset and then enabled.
*
* \param vectorTableOffset The offset of the vector table base address from
* memory address 0x00000000. The offset should be multiple to 1024 bytes.
* \param waitus The timeout value in microsecond used to wait for core to be
* booted. value zero is for infinite wait till the core is booted successfully.
*
*******************************************************************************/
void Cy_SysEnableCM33(uint32_t vectorTableOffset, uint32_t waitus)
{
    uint32_t interruptState;
    uint32_t cpuState;
    uint32_t regValue;

    interruptState = Cy_SysLib_EnterCriticalSection();

    cpuState = Cy_SysGetCM33Status();
    if (CY_SYS_CORE_STATUS_ACTIVE == cpuState)
    {
        Cy_SysResetCM33(CY_SYS_CORE_WAIT_10US);
    }

    MXCM33->CM33_S_VECTOR_TABLE_BASE = vectorTableOffset;

    regValue = MXCM33->CM33_CMD & ~(MXCM33_CM33_CMD_ENABLED_Msk | MXCM33_CM33_CMD_VECTKEYSTAT_Msk);
    regValue |= _VAL2FLD(MXCM33_CM33_CMD_VECTKEYSTAT, CY_SYS_CORE_PWR_CTL_KEY_OPEN); /* set key bits */
    regValue |= _VAL2FLD(MXCM33_CM33_CMD_ENABLED, CY_SYS_CM33_IN_RESET); /* reset enable bit */
    MXCM33->CM33_CMD = regValue;

    if (waitus == CY_SYS_CORE_WAIT_INFINITE)
    {
        while (Cy_SysGetCM33Status() != CY_SYS_CORE_STATUS_ACTIVE)
        {
            /* Wait for the power mode to take effect */
        }
    }
    else
    {
        if (Cy_SysGetCM33Status() != CY_SYS_CORE_STATUS_ACTIVE)
        {
            Cy_SysLib_DelayUs(waitus);
        }
    }

    MXCM33->CM33_CTL &= ~(_VAL2FLD(MXCM33_CM33_CTL_CPU_WAIT, CY_SYS_CPU_WAIT_DEFAULT));

    /* Enable Event from CM55 */
    MXCM33->CM33_EVENT_CTL = CM55_0_CPU_EVENT;

    Cy_SysLib_ExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Cy_SysResetCM33
****************************************************************************//**
*
* Resets the Cortex-M33 core and waits for the mode to take the effect.
*
* \param waitus The timeout value in microsecond used to wait for core to be
* reset. value zero is for infinite wait till the core is reset successfully.
*
* \warning Do not call the function while the Cortex-M33 is executing because
* such a call may corrupt/abort a pending bus-transaction by the CPU and cause
* unexpected behavior in the system including a deadlock. Call the function
* while the Cortex-M55 core is in the Sleep or Deep Sleep low-power mode. Use
* the \ref group_syspm Power Management (syspm) API to put the CPU into the
* low-power modes. Use the \ref Cy_SysPm_ReadStatus() to get a status of the CPU.
*
*******************************************************************************/
void Cy_SysResetCM33(uint32_t waitus)
{
    uint32_t interruptState;
    uint32_t regValue;

    interruptState = Cy_SysLib_EnterCriticalSection();

    regValue = MXCM33->CM33_CMD & ~(MXCM33_CM33_CMD_ENABLED_Msk | MXCM33_CM33_CMD_VECTKEYSTAT_Msk);
    regValue |= _VAL2FLD(MXCM33_CM33_CMD_VECTKEYSTAT, CY_SYS_CORE_PWR_CTL_KEY_OPEN); /* set key bits */
    regValue |= _VAL2FLD(MXCM33_CM33_CMD_ENABLED, CY_SYS_CM33_IN_RESET); /* reset enable bit */
    MXCM33->CM33_CMD = regValue;

    if (waitus == CY_SYS_CORE_WAIT_INFINITE)
    {
        /* After SW clears this field to '0', HW automatically sets this field to '1'.
         * This effectively results in a CM33 reset, followed by a CM33 warm boot. */
        while ( _FLD2VAL(MXCM33_CM33_CMD_ENABLED, MXCM33->CM33_CMD) != CY_SYS_CM33_NOT_IN_RESET)
        {
            /* Wait for the power mode to take effect */
        }
    }
    else
    {
        if ( _FLD2VAL(MXCM33_CM33_CMD_ENABLED, MXCM33->CM33_CMD) != CY_SYS_CM33_NOT_IN_RESET)
        {
            Cy_SysLib_DelayUs(waitus);
        }
    }

    Cy_SysLib_ExitCriticalSection(interruptState);
}

#endif /* (CY_SYSTEM_CPU_M0P == 1UL) || defined(CY_DOXYGEN) */

#if defined(__cplusplus)
}
#endif
