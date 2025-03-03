/*
 * blink_task.h
 *
 *  Created on: Nov 24, 2022
 *      Author: wiroon
 */

#ifndef SOURCE_BLINK_TASK_H_
#define SOURCE_BLINK_TASK_H_

#include "FreeRTOS.h"
#include "task.h"

void task_blink(void* param);
void LED_blink_control(int stage);


#endif /* SOURCE_BLINK2_TASK_H_ */
