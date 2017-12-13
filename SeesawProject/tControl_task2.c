/*
 * tControl.c
 *
 *  Created on: 08.09.2017
 *      Author: mac, jzilly
 */

/* Includes ------------------------------------------------------------------*/
#include "tControl.h"
#include "cmsis_os.h"
#include "usart.h"
#include "tLowPass.h"
#include "tControlP.h"
#include "tControlPID.h"
#include "tControlLeadLag.h"
#include <math.h>

struct signalPackage seeSig;
char inSignalWrite = 0;

/*
---------------------- TASK 2 ------------------------------------------
*/

/* vtControlStartTask function */
void vtControlStartTask(void const * argument) {
	/* local constants  ------------------------------------------------- */
	const uint16_t uiMotorBaseSpeed = 9; /* motor base speed */
	const double dAngleCorrectionConst = 0.4;
	const double dMagnitudeStep = 5000.0;
	const double dPeriod = 2400; // Period length constant of reference signal

	/* local variables -------------------------------------------------- */
	xMotorPWMCommand_t xMotorCommandBuffer; /* Buffer contains motor PWM values, to be sent to motor task*/
	xIMUDATA_t xIMUDataBuffer; /* Buffer contains IMU read outs, came in from gyro task*/
	double dAnglePos; /* max variation of motor base speed*/
	double tLast = 0.0;
	double polarity = 1.0;
	uint8_t  uiCounter = 0;
	double r = -dMagnitudeStep; // INITIAL REFERENCE SIGNAL
	double dN = 0.0; // COUNT FOR REFERENCE SIGNAL


	while (1) {
		/* Reading IMU data from the Queue*/
		osEvent evt = osMailGet(GyrodataQueueHandle, 50);
		if (evt.status == osEventMail) {
			xIMUDATA_t *IMUData = (xIMUDATA_t *) evt.value.p;
			xIMUDataBuffer.AccelX = IMUData->AccelX;
			xIMUDataBuffer.AccelY = IMUData->AccelY;
			xIMUDataBuffer.AccelZ = IMUData->AccelZ;
			xIMUDataBuffer.GyroX = IMUData->GyroX;
			xIMUDataBuffer.GyroY = IMUData->GyroY;
			xIMUDataBuffer.GyroZ = IMUData->GyroZ;
			osMailFree(GyrodataQueueHandle, IMUData);
		}

		// STEP REFERENCE INPUT
		dN++;
		if (dN > dPeriod)
			{
			dN = 0; // Enforce bounds on dN
			r += polarity * dMagnitudeStep; // Step response
			uiCounter += 1;
			if (uiCounter > 1)
				{
				polarity *= -1;
				uiCounter = 0;
				}
			}

		dAnglePos = (double) xIMUDataBuffer.AccelX;


		/* calculation of the control input */
		double systemTime = (double) xTaskGetTickCount();
		double dt = (systemTime - tLast)*0.001; // milliseconds to second conversion
		tLast = systemTime;

		// CONTROLLER - Error signal is calculated in dPIDabc
		double u = dPID(r, dAnglePos, dt);



		/* signal transmission */
		inSignalWrite = 1;
		seeSig.y = dAnglePos;
		seeSig.u = u;
		seeSig.r = r;

		inSignalWrite = 0;

		/* Control starts here */
		xMotorCommandBuffer.Motor1 = uiMotorBaseSpeed
				+ (uint16_t) 100 * u * dAngleCorrectionConst;
		xMotorCommandBuffer.Motor2 = uiMotorBaseSpeed
				- (uint16_t) 100 * u * dAngleCorrectionConst;
		/* Control ends here */

		/* send data to Queue */
		osMailPut(MotorcommandQueueHandle, &xMotorCommandBuffer);

	}
}

