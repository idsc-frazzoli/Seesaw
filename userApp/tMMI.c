/*
 * tMMI.c
 *
 * Man-Machine-Interface
 *
 *
 *  Created on: 07.09.2017
 *      Author: mac
 *
 *
 *   ATTENTION
 *   This task is fullfilled mit special informational Funktions.
 *   Fingergrabbing and changelin the parameters from the computers is
 *   allowed for die experts only! So all the lefthanders stay away
 *   and do not disturben the flux von here working algortimens.
 *   Otherwise you will be thrown out of github and banned from
 *   the internet!
 *   Therfore: please keep still and only watchen astaunished the blinkenlights.
 *
 *
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "tMMI.h"





void vtMMIStartTask(void const * argument)
{
	 while(1)
	  {
		  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3); /* LED heartbeat */
		  osDelay(1000);


	  }
}
