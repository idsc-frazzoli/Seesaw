/*
 * tControl.h
 *
 * This task runs the controller. It takes measurements from the
 * gyro task, calculates the needed motor value and forwards them
 * to the motor task.
 *
 *  Created on: 08.09.2017
 *      Author: mac
 */

#ifndef TCONTROL_H_
#define TCONTROL_H_

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "../userApp/dVariables.h"



/* Variables -----------------------------------------------------------------*/
extern osMessageQId MotorcommandQueueHandle;
extern osMessageQId GyrodataQueueHandle;

#pragma pack(push, 1) // exact fit - no padding
struct signalPackage{
	double e;
	double u;
};
#pragma pack(pop) //back to whatever the previous packing mode was

extern struct signalPackage seeSig;
extern char inSignalWrite;

/* Function prototypes -------------------------------------------------------*/
void vtControlStartTask(void const * argument);
void vReadDataFromQueue(osMessageQId *GyrodataQueueHandle, xIMUDATA_t *xIMUDataBuffer );



#endif /* TCONTROL_H_ */
