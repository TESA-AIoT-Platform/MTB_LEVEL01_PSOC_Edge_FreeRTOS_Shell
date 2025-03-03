/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for CM33 Secure Project.
*
* Related Document: See README.md
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
#ifdef ENABLE_HAL_RETARGET_IO
#include "cy_retarget_io.h"
#endif
#include "partition_ARMCM33.h"
#include "cy_ms_ctl.h"

/*****************************************************************************
* Macros
*****************************************************************************/
#define NS_APP_BOOT_ADDR                 CY_CM33_NS_APP_BOOT_ADDR
#define CM33_NS_SP_STORE                 (NS_APP_BOOT_ADDR)
#define CM33_NS_RESET_HANDLER_STORE      (NS_APP_BOOT_ADDR + 4)

/*****************************************************************************
* Function Definitions
*****************************************************************************/
typedef void (*funcptr_void) (void) __attribute__((cmse_nonsecure_call));
void config_ppc(void);
void config_pc(void);
void config_mpc(void);
void config_sema(void);
void release_uart(void);
cy_en_ms_ctl_status_t config_set_cm33_ns_pc(void);

/*****************************************************************************
* Function Name: main
******************************************************************************
* This is the main function for Cortex M33 CPU secure application
* NOTE: CM33 secure project assumes that certain memory and peripheral regions
* will be accessed from Non secure environment by the CM33 NS /CM55 code,
* For such regions MPC and PPC configurations are applied to make it non secure
* Any access to these regions from the secure side recommended to be done before the
* MPC/PPC configuration is applied.Once any memory or peripheral region is marked
* as non secure it cannot be accessed from the secure side using secure aliased address 
* but may be accessed using non secure aliased address
*****************************************************************************/
int main(void)
{
    uint32_t ns_stack;
    funcptr_void NonSecure_ResetHandler;
    cy_rslt_t result;

    /* Trustzone setup */
    TZ_SAU_Setup();

#if defined (__FPU_USED) && (__FPU_USED == 1U) && \
      defined (TZ_FPU_NS_USAGE) && (TZ_FPU_NS_USAGE == 1U)
    /*FPU init*/
    initFPU();
#endif

    /* Set up internal routing, pins, and clock-to-peripheral connections */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

#ifdef ENABLE_HAL_RETARGET_IO
    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                                 CY_RETARGET_IO_BAUDRATE);
    /* retarget-io init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");
    printf("****************** "
           "PSOC Edge MCU: CM33 Secure App start "
           "****************** \r\n\n");

    release_uart();
#endif


    /*Enables the PD1 Power Domain*/
    Cy_System_EnablePD1();

    /* SPERI Registers - Enable APP_MMIO_TCM IP through PERI[1].PERI2_0.PERI_GROUP_STRUCT[4].SL_CTL register */
    Cy_SysClk_PeriGroupSlaveInit(CY_MMIO_CM55_TCM_512K_PERI_NR, CY_MMIO_CM55_TCM_512K_GROUP_NR, \
                                 CY_MMIO_CM55_TCM_512K_SLAVE_NR, CY_MMIO_CM55_TCM_512K_CLK_HF_NR);

    /*Enable SOCMEM*/
    Cy_SysEnableSOCMEM(true);

    /* configure sempahore */
    config_sema();

    /*configure MPC for NS*/
    config_mpc();

    ns_stack = (uint32_t)(*((uint32_t*)CM33_NS_SP_STORE));
    __TZ_set_MSP_NS(ns_stack);

    NonSecure_ResetHandler = (funcptr_void)(*((uint32_t*)CM33_NS_RESET_HANDLER_STORE));

    /*configure PPC for NS*/
    config_ppc();

    /* Start non-secure application */
    NonSecure_ResetHandler();

    for (;;)
    {
    }
}

#ifdef ENABLE_HAL_RETARGET_IO
/*******************************************************************************
* Function Name: release_uart
****************************************************************************//**
*
*******************************************************************************/
void release_uart(void)
{
    cy_retarget_io_deinit();

    Cy_GPIO_SetHSIOM_SecPin(P6_7_PORT, P6_7_PIN, 1);
    Cy_GPIO_SetHSIOM_SecPin(P6_5_PORT, P6_5_PIN, 1);

}
#endif
/* [] END OF FILE */

