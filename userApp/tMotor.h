/*
 * tMotor.h
 *
 *This task takes the motor values from the control task and writes
 *them to the motors.
 *
 *  Created on: 08.09.2017
 *      Author: mac
 */

#ifndef TMOTOR_H_
#define TMOTOR_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"
#include "cmsis_os.h"
#include "dVariables.h"

/* Variables -----------------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern osMessageQId MotorcommandQueueHandle;

/* Function prototypes -------------------------------------------------------*/
void vtMotorStartTask(void const * argument);
void vSetPWM(TIM_HandleTypeDef timHandle, uint32_t ulChannel, uint16_t uiPWMDutyCycle);

#endif /* TMOTOR_H_ */
