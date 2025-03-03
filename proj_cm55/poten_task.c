/*
 * poten_task.c
 *
 *  Created on: Mar 2, 2025
 *      Author: sriborrirux
 */

#include "poten_task.h"

#include "cybsp.h"
#include "cyhal.h"
#include "FreeRTOS.h"
#include "cycfg.h"
#include "cy_retarget_io.h"

/*******************************************************************************
* Global Variables
*******************************************************************************/
int adc_raw_out =0; // ADC conversion result

void task_poten(void* param) {

  /* Suppress warning for unused parameter */
  (void) param;

    cy_rslt_t result;
	cyhal_adc_t adc_obj;
	cyhal_adc_channel_t adc_chan_0_obj;

	/* Initialize ADC. The ADC block which can connect to pin 15[1] is selected */
	result = cyhal_adc_init(&adc_obj, P15_1, NULL);

	// ADC configuration structure
	const cyhal_adc_config_t ADCconfig ={
		.continuous_scanning = false,
		.resolution = 12,
		.average_count = 1,
		.average_mode_flags = 0,
		.ext_vref_mv = 0,
		.vneg = CYHAL_ADC_VNEG_VREF,
		.vref = CYHAL_ADC_REF_VDDA,
		.ext_vref = NC,
		.is_bypassed = false,
		.bypass_pin = NC
	};

	// Configure to use VDD as Vref
	result = cyhal_adc_configure(&adc_obj, &ADCconfig);

	/* Initialize ADC channel, allocate channel number 0 to pin 15[1] as this is the first channel initialized */
	const cyhal_adc_channel_config_t channel_config = { .enable_averaging = false, .min_acquisition_ns = 220, .enabled = true };
	result = cyhal_adc_channel_init_diff(&adc_chan_0_obj, &adc_obj, P15_1, CYHAL_ADC_VNEG, &channel_config);



      for (;;)
      {
    	  /* Read the ADC conversion result for corresponding ADC channel. Repeat as necessary. */
    	  		adc_raw_out = cyhal_adc_read_uv(&adc_chan_0_obj);

      }
}

/*******************************************************************************
* Function Name: poten_status
********************************************************************************
* Summary:
*  This function reads the potentiometer value.
*******************************************************************************/
void print_poten_status()
{
		printf("POTEN's value = %d\n",adc_raw_out);
}


