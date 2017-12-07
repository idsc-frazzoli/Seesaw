/*
 * tControl.c
 *
 *  Created on: 08.09.2017
 *      Author: mac
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

/* vtControlStartTask function */
void vtControlStartTask(void const * argument) {
	/* local variables -------------------------------------------------- */
	xMotorPWMCommand_t xMotorCommandBuffer; /* Buffer contains motor PWM values, to be sent to motor task*/
	xIMUDATA_t xIMUDataBuffer; /* Buffer contains IMU read outs, came in from gyro task*/
	double dAnglePos, dAngleCorrectionConst = 0.4; /* max variation of motor base speed*/
	double dAnglePosPrev = 0.0;
	/* local constants  ------------------------------------------------- */

//	const double dMotorTrustConsta = 9.1493e-6, dMotorTrustConstb = 6.7674e-4,
//			dMotorTrustConstc = 5.48456e-4; /* motor constants derived from Mike Hammers paper*/
	const uint16_t uiMotorBaseSpeed = 9; /* motor base speed, PWM value [40 ... 100];*/
	double tLast = 0.0;

	double r = 0.0;
	double dN = 0.0; // COUNT FOR REFERENCE SIGNAL
	double dPeriod = 600; // Period length constant of reference signal

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

		/* Normalize the measured angle to [-1...1]*/
		r = 0 ; //6000*sin(dN/dPeriod);
		dN++;
		if (dN > 2*3.14*dPeriod) dN = 0; // Enforce bounds on dN

		dAnglePos = (double) xIMUDataBuffer.AccelX;

		dAnglePosPrev = dAnglePos;


		dAnglePos = dAnglePos - r; // Create difference to reference signal

		/* calculation of the control input */
		double systemTime = (double) xTaskGetTickCount();
		double dt = (systemTime - tLast); //*0.001;
		tLast = systemTime;

		double e = dLP(dAnglePos, dt);
		// double u = dLeadLag(dAnglePos, dt);
		//double u = dP(dAnglePos);
		double u = dPID(dAnglePos,e,dt);
		//double u = dLeadLag(e, dt);
		//double u = dP(e);



		/* signal transmission */
		inSignalWrite = 1;
		seeSig.y = dAnglePos;
		seeSig.u = u;
		seeSig.r = r;

		inSignalWrite = 0;

		/* Control starts here */
		xMotorCommandBuffer.Motor1 = uiMotorBaseSpeed
				- (uint16_t) 100 * u * dAngleCorrectionConst;
		xMotorCommandBuffer.Motor2 = uiMotorBaseSpeed
				+ (uint16_t) 100 * u * dAngleCorrectionConst;
		/* Control ends here */

		/* send data to Queue */
		osMailPut(MotorcommandQueueHandle, &xMotorCommandBuffer);

	}
}

