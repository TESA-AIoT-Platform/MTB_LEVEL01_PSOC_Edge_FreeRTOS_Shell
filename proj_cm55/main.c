/******************************************************************************
* File Name:   main.c
*
* Created by Assoc. Prof. Wiroon Sriborrirux
*
*******************************************************************************/

/* Header file includes */
#include <blink_task.h>
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "poten_task.h"

#include "FreeRTOS.h"
#include "task.h"

#include "usrcmd.h"

int main()
{
    cy_rslt_t result;

    /* Initialize the board support package. */
    result = cybsp_init();
    CY_ASSERT(CY_RSLT_SUCCESS == result);

    /* Initialize the User LED */
       result = cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT,
           CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);

       /* Initialize the GPIO */
       CY_ASSERT(CY_RSLT_SUCCESS == result);

    /* To avoid compiler warnings. */
       (void) result;

    /* Enable global interrupts. */
    	__enable_irq();

    /* Create the LED Blinking task. */
    xTaskCreate(task_blink, "blink task", configMINIMAL_STACK_SIZE,
        NULL, configMAX_PRIORITIES - 7, NULL);

    /* Initialize retarget-io to use the debug UART port. */
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                        CY_RETARGET_IO_BAUDRATE);


    /* \x1b[2J\x1b[;H - ANSI ESC sequence to clear screen. */
    printf("\x1b[2J\x1b[;H");

    // Stack size in WORDs
    // Idle task = priority 0
     xTaskCreate(task_poten, "POTEN" ,configMINIMAL_STACK_SIZE*4,
    		 0 /* args */ ,0 /* priority */, 0);

    // Start BDH Shell
    xTaskCreate(usrcmd_task, "usrcmd_task", configMINIMAL_STACK_SIZE*4,
    		0 /* args */ ,0 /* priority */, 0);

    /* Start the FreeRTOS scheduler. */
    vTaskStartScheduler();


    /* Should never get here. */
    CY_ASSERT(0);
}

/* [] END OF FILE */
