/******************************************************************************
* File Name:   security_config.c
*
* Description: This is the security configuration applied by the CM33 secure project
*
*
*******************************************************************************
* Copyright 2023-2024, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/
#include "cyhal.h"
#include "cybsp.h"
#include "partition_ARMCM33.h"
#include "cy_ppc.h"
#include "cy_mpc.h"
#include "cy_ms_ctl.h"
#include "ifx_se_platform.h"
#include "ifx_se_crc32.h"
/*****************************************************************************
* Macros
*****************************************************************************/

/* Protection context for cm33 */
#define CM33_NS_PC_VALUE                 (5u)
#define CM33_S_PC_VALUE                  (2u)

#define CY_IPC_EP_CYPIPE_CM33_ADDR       (1UL)    //EP1 Index of Endpoint Array
#define SMIF_0_CORE_0_DESELECT_DELAY     (7u)
#define TIMEOUT_1_MS                    (1000UL)  /* 1 ms timeout for all blocking functions */

/*****************************************************************************
* Global variables
*****************************************************************************/
static cy_stc_ppc_init_t ppcInit;
static cy_stc_ppc_attribute_t ppcAttribute;
static cy_stc_ppc_pc_mask_t pcMaskConfig;

/** Place in secure shared memory for semaphore */
CY_SECTION_SHAREDMEM_SEC
static uint32_t ipcSemaArray_sec[CY_IPC_SEMA_COUNT / CY_IPC_SEMA_PER_WORD];

/** Place in normal shared memory for semaphore */
CY_SECTION_SHAREDMEM
static uint32_t ipcSemaArray[CY_IPC_SEMA_COUNT / CY_IPC_SEMA_PER_WORD];

CY_SECTION_SHAREDMEM
static cy_stc_ipc_sema_t ipcSema;
/*****************************************************************************
* Function Definitions
*****************************************************************************/
static void config_ppc0(void);
static void config_ppc1(void);
static void config_smif0_xip_ns(void);
static void config_smif1_xip_ns(void);

/*****************************************************************************
* Function Name: config_sram0_ns
******************************************************************************
* Summary:
* Configures the MPC for SRAM0 non secure regions
*
* Parameters:
* none
*
* Return:
* void
*****************************************************************************/
void config_sram0_ns(void)
{
    cy_stc_mpc_rot_cfg_t rotConfig;

    rotConfig.addrOffset = CY_SRAM0_NS_OFFSET;
    rotConfig.size = CY_SRAM0_NS_SIZE ;
    rotConfig.regionSize = CY_MPC_SIZE_4KB ;
    rotConfig.secure = CY_MPC_NON_SECURE ;
    rotConfig.access = CY_MPC_ACCESS_RW ;

    rotConfig.pc = CY_MPC_PC_2 ;
    Cy_Mpc_ConfigRotMpcStruct(RAMC0_MPC0, &rotConfig);

    rotConfig.pc = CY_MPC_PC_5 ;
    Cy_Mpc_ConfigRotMpcStruct(RAMC0_MPC0, &rotConfig);

    rotConfig.pc = CY_MPC_PC_6 ;
    Cy_Mpc_ConfigRotMpcStruct(RAMC0_MPC0, &rotConfig);
}
/*****************************************************************************
* Function Name: config_sram1_ns
******************************************************************************
* Summary:
* Configures the MPC for SRAM1 non secure regions
*
* Parameters:
* none
*
* Return:
* void
*****************************************************************************/
void config_sram1_ns(void)
{
    cy_stc_mpc_rot_cfg_t rotConfig;

    rotConfig.addrOffset = CY_SRAM1_NS_OFFSET;
    rotConfig.size = CY_SRAM1_NS_SIZE;
    rotConfig.regionSize = CY_MPC_SIZE_4KB ;
    rotConfig.secure = CY_MPC_NON_SECURE ;
    rotConfig.access = CY_MPC_ACCESS_RW ;

    rotConfig.pc = CY_MPC_PC_2 ;
    Cy_Mpc_ConfigRotMpcStruct(RAMC1_MPC0, &rotConfig);

    rotConfig.pc = CY_MPC_PC_5 ;
    Cy_Mpc_ConfigRotMpcStruct(RAMC1_MPC0, &rotConfig);

    rotConfig.pc = CY_MPC_PC_6 ;
    Cy_Mpc_ConfigRotMpcStruct(RAMC1_MPC0, &rotConfig);

    rotConfig.addrOffset = CY_SRAM1_SHM_NS_OFFSET;
    rotConfig.size = CY_SRAM1_SHM_NS_SIZE;
    rotConfig.regionSize = CY_MPC_SIZE_4KB ;
    rotConfig.secure = CY_MPC_NON_SECURE ;
    rotConfig.access = CY_MPC_ACCESS_RW ;

    rotConfig.pc = CY_MPC_PC_2 ;
    Cy_Mpc_ConfigRotMpcStruct(RAMC1_MPC0, &rotConfig);

    rotConfig.pc = CY_MPC_PC_5 ;
    Cy_Mpc_ConfigRotMpcStruct(RAMC1_MPC0, &rotConfig);

    rotConfig.pc = CY_MPC_PC_6 ;
    Cy_Mpc_ConfigRotMpcStruct(RAMC1_MPC0, &rotConfig);
}

/*****************************************************************************
* Function Name: config_rram_nvm_main_ns
******************************************************************************
* Summary:
* Configures the MPC for RRAM non secure regions
*
* Parameters:
* none
*
* Return:
* void
*****************************************************************************/
void config_rram_nvm_main_ns(void)
{
    ifx_se_mpc_rot_cfg_t rotConfig;
    ifx_se_mpc_rot_cfg_crc_t rotConfigCrc;

    rotConfig.addr_offset = CY_RRAM_MAIN_NVM_NS_OFFSET;
    rotConfig.size = CY_RRAM_MAIN_NVM_NS_SIZE;
    rotConfig.region_size = IFX_SE_MPC_SIZE_4KB ;
    rotConfig.secure = IFX_SE_MPC_NON_SECURE ;
    rotConfig.access = IFX_SE_MPC_ACCESS_RW ;

    rotConfig.pc = IFX_SE_MPC_PC_2 ;
    rotConfigCrc.mpc_config = rotConfig;
    rotConfigCrc.crc = IFX_CRC32_CALC((uint8_t *)(&rotConfigCrc), sizeof(rotConfigCrc) - sizeof(uint32_t));
    ifx_se_mpc_config_rot_mpc_struct(&rotConfigCrc, IFX_SE_NULL_CTX);

    rotConfig.pc = IFX_SE_MPC_PC_5 ;
    rotConfigCrc.mpc_config = rotConfig;
    rotConfigCrc.crc = IFX_CRC32_CALC((uint8_t *)(&rotConfigCrc), sizeof(rotConfigCrc) - sizeof(uint32_t));
    ifx_se_mpc_config_rot_mpc_struct(&rotConfigCrc, IFX_SE_NULL_CTX);

    rotConfig.pc = IFX_SE_MPC_PC_6 ;
    rotConfigCrc.mpc_config = rotConfig;
    rotConfigCrc.crc = IFX_CRC32_CALC((uint8_t *)(&rotConfigCrc), sizeof(rotConfigCrc) - sizeof(uint32_t));
    ifx_se_mpc_config_rot_mpc_struct(&rotConfigCrc, IFX_SE_NULL_CTX);

}

/*****************************************************************************
* Function Name: config_socmemram_ns
******************************************************************************
* Summary:
* Configures the MPC for SOCMEM non secure regions
*
* Parameters:
* none
*
* Return:
* void
*****************************************************************************/
void config_socmemram_ns(void)
{
    cy_stc_mpc_rot_cfg_t rotConfig;

    rotConfig.addrOffset = CY_SOCMEMSRAM_NS_OFFSET;
    rotConfig.size = CY_SOCMEMSRAM_NS_SIZE;
    rotConfig.regionSize = CY_MPC_SIZE_8KB ;
    rotConfig.secure = CY_MPC_NON_SECURE ;
    rotConfig.access = CY_MPC_ACCESS_RW ;

    rotConfig.pc = CY_MPC_PC_2 ;
    Cy_Mpc_ConfigRotMpcStruct((MPC_Type*)SOCMEM_SRAM_MPC0, &rotConfig);
    rotConfig.pc = CY_MPC_PC_5 ;
    Cy_Mpc_ConfigRotMpcStruct((MPC_Type*)SOCMEM_SRAM_MPC0, &rotConfig);
    rotConfig.pc = CY_MPC_PC_6 ;
    Cy_Mpc_ConfigRotMpcStruct((MPC_Type*)SOCMEM_SRAM_MPC0, &rotConfig);
}

/*****************************************************************************
* Function Name: config_mpc
******************************************************************************
* Summary:
* Configures the MPC for non secure regions
*
* Parameters:
* none
*
* Return:
* void
*****************************************************************************/
/** Configure MPC for Non-Sec Core */
void config_mpc(void)
{
    config_sram0_ns();
    config_sram1_ns();
    config_rram_nvm_main_ns();
    config_socmemram_ns();
    Cy_Mpc_SetViolationResponse((MPC_Type*)SOCMEM_SRAM_MPC0, true);
    config_smif0_xip_ns();
    config_smif1_xip_ns();

}

/*****************************************************************************
* Function Name: config_ppc
******************************************************************************
* Summary:
* Configures the PPC for non secure peripheral regions
* Note: See Product TRM for information about the PPC regions
*
* Parameters:
* none
*
* Return:
* void
*****************************************************************************/
void config_ppc(void)
{
    config_ppc0();
    config_ppc1();
}
/*****************************************************************************
* Function Name: config_ppc0
******************************************************************************
* Summary:
* Configures the PPC for non secure PERI0 regions
*
* Parameters:
* none
*
* Return:
* void
*****************************************************************************/
void config_ppc0(void)
{
    PPC_Type* ppcPtr;
    cy_en_ppc_status_t ppcStatus;

    /* Configure PPC0 for CM33 access */
    ppcPtr = PPC0;

    // Initialize PPC
    ppcInit.respConfig = CY_PPC_BUS_ERR;
    ppcStatus = Cy_Ppc_InitPpc(ppcPtr, &ppcInit);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    ppcAttribute.secAttribute = CY_PPC_NON_SECURE;
    ppcAttribute.secPrivAttribute = CY_PPC_SEC_NONPRIV;
    ppcAttribute.nsPrivAttribute = CY_PPC_NON_SEC_NONPRIV;


    /*Peri 0,  Address 0x42000000*/
    ppcAttribute.startRegion = PROT_PERI0_MAIN;
    ppcAttribute.endRegion = PROT_PERI0_MAIN;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x42004040 - 0x42004140 */
    ppcAttribute.startRegion = PROT_PERI0_GR1_GROUP;
    ppcAttribute.endRegion = PROT_PERI0_GR5_GROUP;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /*Peri 0,  Address 0x42008000 */
    ppcAttribute.startRegion = PROT_PERI0_TR;
    ppcAttribute.endRegion = PROT_PERI0_TR;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0,  Address 0x42040000*/
    ppcAttribute.startRegion = PROT_PERI0_PERI_PCLK0_MAIN;
    ppcAttribute.endRegion = PROT_PERI0_PERI_PCLK0_MAIN;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0,  Address 0x42204000*/
    ppcAttribute.startRegion = PROT_PERI0_RRAMC0_RRAM_EXTRA_AREA_RRAMC_GENERAL;
    ppcAttribute.endRegion = PROT_PERI0_RRAMC0_RRAM_EXTRA_AREA_RRAMC_GENERAL;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0,  Address 0x42210000 - 0x42210020 */
    ppcAttribute.startRegion = PROT_PERI0_RRAMC0_RRAMC0_RRAMC_USER;
    ppcAttribute.endRegion = PROT_PERI0_RRAMC0_RRAMC0_RRAMC_ALLUSER;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x42213000*/
    ppcAttribute.startRegion = PROT_PERI0_RRAMC0_RRAM_SFR_RRAMC_SFR_USER;
    ppcAttribute.endRegion = PROT_PERI0_RRAMC0_RRAM_SFR_RRAMC_SFR_USER;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x42220000 - 0x42230000 */
    ppcAttribute.startRegion = PROT_PERI0_M33SYSCPUSS;
    ppcAttribute.endRegion = PROT_PERI0_RAMC1_CM33;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x42240100 - 0x42240200 */
    ppcAttribute.startRegion = PROT_PERI0_RAMC0_RAM_PWR;
    ppcAttribute.endRegion = PROT_PERI0_RAMC1_RAM_PWR;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);
    
    /* Peri 0, Address 0x42260000*/
    ppcAttribute.startRegion = PROT_PERI0_MXCM33_CM33;
    ppcAttribute.endRegion = PROT_PERI0_MXCM33_CM33;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);
    
    /* Peri 0, Address 0x42261004*/
    ppcAttribute.startRegion = PROT_PERI0_MXCM33_CM33_NS;
    ppcAttribute.endRegion = PROT_PERI0_MXCM33_CM33_NS;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x42268000 - 0x42290000*/
    ppcAttribute.startRegion = PROT_PERI0_MXCM33_CM33_INT;
    ppcAttribute.endRegion = PROT_PERI0_CPUSS_ALL_PC;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x42290120 - 0x42290200*/
    ppcAttribute.startRegion = PROT_PERI0_CPUSS_CM33_NS;
    ppcAttribute.endRegion = PROT_PERI0_CPUSS_MSC_INT;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x42295004 - 0x42296000*/
    ppcAttribute.startRegion = PROT_PERI0_MS_PC0_PRIV_MIR;
    ppcAttribute.endRegion = PROT_PERI0_MSC_ACG;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x422a0020 - 0x422a01e0*/
    ppcAttribute.startRegion = PROT_PERI0_IPC0_STRUCT1_IPC;
    ppcAttribute.endRegion = PROT_PERI0_IPC0_STRUCT15_IPC;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x422a1040 - 0x42400800 */
    ppcAttribute.startRegion = PROT_PERI0_IPC0_INTR_STRUCT2_INTR;
    ppcAttribute.endRegion = PROT_PERI0_SRSS_HIB_DATA;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x42401000*/
    ppcAttribute.startRegion = PROT_PERI0_SRSS_MAIN;
    ppcAttribute.endRegion = PROT_PERI0_SRSS_MAIN;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x42404000 - 0x42430000*/
    ppcAttribute.startRegion = PROT_PERI0_RAM_TRIM_SRSS_SRAM;
    ppcAttribute.endRegion = PROT_PERI0_DEBUG600_DEBUG600;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x42440000 - 0x42a50000*/
    ppcAttribute.startRegion = PROT_PERI0_CRYPTO_MAIN;
    ppcAttribute.endRegion = PROT_PERI0_I3C;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 0, Address 0x42c10000 - 0x42d80000*/
    ppcAttribute.startRegion = PROT_PERI0_ETH0;
    ppcAttribute.endRegion = PROT_PERI0_MXNNLITE_1_0;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);

    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    // Set PC Mask
    pcMaskConfig.startRegion = PROT_PERI0_MAIN;
    pcMaskConfig.endRegion = PROT_PERI0_MXNNLITE_1_0;
    pcMaskConfig.pcMask = 0x64U; // max 8 pcs
    ppcStatus = Cy_Ppc_SetPcMask(ppcPtr, &pcMaskConfig);

    if(ppcStatus!=CY_PPC_SUCCESS) CY_ASSERT(0);
}


/*****************************************************************************
* Function Name: config_ppc1
******************************************************************************
* Summary:
* Configures the PPC for non secure PERI1 regions
*
* Parameters:
* none
*
* Return:
* void
*****************************************************************************/
void config_ppc1(void)
{
    PPC_Type* ppcPtr;
    cy_en_ppc_status_t ppcStatus;

    ppcPtr = PPC1;

    // Initialize PPC
    ppcInit.respConfig = CY_PPC_BUS_ERR;
    ppcStatus = Cy_Ppc_InitPpc(ppcPtr, &ppcInit);
    
    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    ppcAttribute.secAttribute = CY_PPC_NON_SECURE;
    ppcAttribute.secPrivAttribute = CY_PPC_SEC_NONPRIV;
    ppcAttribute.nsPrivAttribute = CY_PPC_NON_SEC_NONPRIV;
    
    /* Peri 1, Address 0x44000000 - 0x44004110 */
    ppcAttribute.startRegion = PROT_PERI1_MAIN;
    ppcAttribute.endRegion = PROT_PERI1_GR4_GROUP;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);
    
    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 1, Address 0x44008000 */
    ppcAttribute.startRegion = PROT_PERI1_TR;
    ppcAttribute.endRegion = PROT_PERI1_TR;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);
    
    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 1, Address 0x44040000 - 0x44161004 */
    ppcAttribute.startRegion = PROT_PERI1_PERI_PCLK1_MAIN;
    ppcAttribute.endRegion = PROT_PERI1_MXCM55_CM55_NS;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);
    
    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);
 
    /* Peri 1, Address 0x44168000 - 0x441c1000 */
    ppcAttribute.startRegion = PROT_PERI1_MXCM55_CM55_INT;
    ppcAttribute.endRegion = PROT_PERI1_APPCPUSS_AP;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);
    
    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 1, Address 0x441c50d0 - 0x44440800 */
    ppcAttribute.startRegion = PROT_PERI1_MS_CTL_MS_PC13_PRIV_MIR;
    ppcAttribute.endRegion = PROT_PERI1_SMIF0_CORE1_DEVICE;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);
    
    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 1, Address 0x44424000 - 0x44640000 */
    ppcAttribute.startRegion = PROT_PERI1_SMIF0_CORE0_SMIF_HSIOM_SMIF_PRT0_PRT;
    ppcAttribute.endRegion = PROT_PERI1_SOCMEM_MAIN;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);
    
    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 1, Address 0x44640200 - 0x44640200 */
    ppcAttribute.startRegion = PROT_PERI1_SOCMEM_SOCMEM_PWR;
    ppcAttribute.endRegion = PROT_PERI1_SOCMEM_SOCMEM_PWR;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);
    
    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

    /* Peri 1, Address 0x44650000 - 0x48040000 */
    ppcAttribute.startRegion = PROT_PERI1_SOCMEM_MAIN_PORT;
    ppcAttribute.endRegion = PROT_PERI1_DTCM;
    ppcStatus = Cy_Ppc_ConfigAttrib(ppcPtr, &ppcAttribute);
    
    CY_ASSERT(ppcStatus==CY_PPC_SUCCESS);

     // Set PC Mask
    pcMaskConfig.startRegion = PROT_PERI1_MAIN;
    pcMaskConfig.endRegion = PROT_PERI1_DTCM;
    pcMaskConfig.pcMask = 0x64U; // max 8 pcs
    ppcStatus = Cy_Ppc_SetPcMask(ppcPtr, &pcMaskConfig);

    if(ppcStatus!=CY_PPC_SUCCESS) CY_ASSERT(0);
}


/*****************************************************************************
* Function Name: config_smif0_xip_ns
******************************************************************************
* Summary:    Configures the MPC for non secure SMIF0 regions
*
* Parameters:
* none
*
* Return:
* void
*****************************************************************************/
void config_smif0_xip_ns(void)
{
    cy_stc_mpc_rot_cfg_t rotConfig;

    rotConfig.addrOffset = CY_SMIF0_MAIN_NVM_NS_OFFSET;
    rotConfig.size = CY_SMIF0_MAIN_NVM_NS_SIZE;
    rotConfig.regionSize = CY_MPC_SIZE_128KB ;
    rotConfig.pc = CY_MPC_PC_2 ;
    rotConfig.secure = CY_MPC_NON_SECURE ;
    rotConfig.access = CY_MPC_ACCESS_RW ;

    Cy_Mpc_ConfigRotMpcStruct((MPC_Type*)SMIF0_CORE0_SLOW_AHB_MPC0, &rotConfig);

    rotConfig.pc = CY_MPC_PC_5 ;
    Cy_Mpc_ConfigRotMpcStruct((MPC_Type*)SMIF0_CORE0_SLOW_AHB_MPC0, &rotConfig);

    rotConfig.pc = CY_MPC_PC_6 ;
    Cy_Mpc_ConfigRotMpcStruct((MPC_Type*)SMIF0_CORE0_SLOW_AHB_MPC0, &rotConfig);
    rotConfig.pc = CY_MPC_PC_6 ;
    Cy_Mpc_ConfigRotMpcStruct((MPC_Type*)SMIF0_CORE0_AXI_MPC0, &rotConfig);
}

/*****************************************************************************
* Function Name: config_smif1_xip_ns
******************************************************************************
* Summary:
* Configures the MPC for non secure SMIF1 regions
*
* Parameters:
* none
*
* Return:
* void
*****************************************************************************/
void config_smif1_xip_ns(void)
{
    cy_stc_mpc_rot_cfg_t rotConfig;
    cy_stc_smif_context_t SMIF_CORE1_Context;

    static const cy_stc_smif_config_t SMIF_0_CORE_1_config =
    {
        .mode = (uint32_t)CY_SMIF_NORMAL,
        .deselectDelay = SMIF_0_CORE_0_DESELECT_DELAY,
        .rxClockSel = (uint32_t)CY_SMIF_SEL_INVERTED_FEEDBACK_CLK,
        .blockEvent = (uint32_t)CY_SMIF_BUS_ERROR,
        .enable_internal_dll = false
    };

    rotConfig.addrOffset = CY_SMIF1_MAIN_NVM_NS_OFFSET;
    rotConfig.size = CY_SMIF1_MAIN_NVM_NS_SIZE;
    rotConfig.regionSize = CY_MPC_SIZE_128KB ;
    rotConfig.pc = CY_MPC_PC_2 ;
    rotConfig.secure = CY_MPC_NON_SECURE ;
    rotConfig.access = CY_MPC_ACCESS_RW ;

    /* Enable IP with default configuration */
    (void) Cy_SMIF_Init(SMIF0_CORE1, &SMIF_0_CORE_1_config, TIMEOUT_1_MS, &SMIF_CORE1_Context);
    Cy_SMIF_Enable(SMIF0_CORE1, &SMIF_CORE1_Context);

    Cy_Mpc_ConfigRotMpcStruct((MPC_Type*)SMIF0_CORE1_SLOW_AHB_MPC0, &rotConfig);

    rotConfig.pc = CY_MPC_PC_5 ;
    Cy_Mpc_ConfigRotMpcStruct((MPC_Type*)SMIF0_CORE1_SLOW_AHB_MPC0, &rotConfig);

    rotConfig.pc = CY_MPC_PC_6 ;
    Cy_Mpc_ConfigRotMpcStruct((MPC_Type*)SMIF0_CORE1_SLOW_AHB_MPC0, &rotConfig);

    rotConfig.pc = CY_MPC_PC_6 ;
    Cy_Mpc_ConfigRotMpcStruct((MPC_Type*)SMIF0_CORE1_AXI_MPC0, &rotConfig);

    /* Disable IP as MPC configuration is complete */
    Cy_SMIF_Disable(SMIF0_CORE1);
}

/*****************************************************************************
* Function Name: config_sema
******************************************************************************
* Summary:
* Initialize global semaphores for secure and non secure
*
* Parameters:
* None
*
* Return:
* void
*****************************************************************************/
void config_sema(void)
{
    ipcSema.maxSema = CY_IPC_SEMA_COUNT;
    ipcSema.arrayPtr = ipcSemaArray;
    ipcSema.arrayPtr_sec = ipcSemaArray_sec;

    /* Initialize global semaphores (for both secure and non-secure)
     * using IPC Channel 4 ( IPC0_SEMA_CH_NUM ) */

    Cy_IPC_Sema_InitExt(IPC0_SEMA_CH_NUM, &ipcSema);
}


/* [] END OF FILE */
