/*
 * tMotor.c
 *
 *  Created on: 08.09.2017
 *      Author: mac
 */

/* Includes ------------------------------------------------------------------*/
#include "tMotor.h"


/* Functions -----------------------------------------------------------------*/

/* vtMotorStartTask function
 * motor task, sets the motor values
 */
void vtMotorStartTask(void const * argument)
{
	xMotorPWMCommand_t	xMotorPWM;

  while(1)
  {
		  /* Reading data from the Queue*/
		  osEvent evt = osMailGet(MotorcommandQueueHandle, 0);
		          if (evt.status == osEventMail)
		          {
		        	  xMotorPWMCommand_t *MotorData = (xMotorPWMCommand_t *) evt.value.p;
		        	  xMotorPWM.Motor1 = MotorData->Motor1;
		        	  xMotorPWM.Motor2 = MotorData->Motor2;
		        	  osMailFree(MotorcommandQueueHandle, MotorData);
		          }

		if(!MOTOR_OFF)
		{
			/* writing the motor PWM values to the PWM driver*/
			vSetPWM(htim2, TIM_CHANNEL_1, xMotorPWM.Motor1);
			vSetPWM(htim2, TIM_CHANNEL_2, xMotorPWM.Motor2);
		}
  }

}




/* modifies the PWM value and writes it into the PWM register
 * @param	uiPWMDutyCycle		PWM in % [1...100]
 */
void vSetPWM(TIM_HandleTypeDef timHandle, uint32_t ulChannel, uint16_t uiPWMDutyCycle)
{
 uint16_t uiPeriod = 1000;
 uint16_t uiPulse;

 /* make sure PWM isn't above 100, and scale it to fit in PWM function*/
 if(uiPWMDutyCycle > 100 )
 {  uiPulse = 1000;  }
 else
 {  uiPulse = uiPWMDutyCycle*10;}

  HAL_TIM_PWM_Stop(&timHandle, ulChannel); /* stop generation of pwm */
 TIM_OC_InitTypeDef sConfigOC;
 timHandle.Init.Period = uiPeriod; /* set the period duration */
 HAL_TIM_PWM_Init(&timHandle); /* reinititialise with new period value */

 sConfigOC.OCMode = TIM_OCMODE_PWM1;
 sConfigOC.Pulse = uiPulse; /* set the pulse duration */
 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
 sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
 HAL_TIM_PWM_ConfigChannel(&timHandle, &sConfigOC, ulChannel);

 HAL_TIM_PWM_Start(&timHandle, ulChannel); /* start pwm generation */
}



