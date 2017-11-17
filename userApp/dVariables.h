/*
 * dVariables.h
 *
 *  Created on: 12.09.2017
 *      Author: mac
 */

#ifndef DVARIABLES_H_
#define DVARIABLES_H_


/* defines -----------------------------------------------------------------*/
#define SEND_MOTOR_DATA_TO_USART	1		/* 1 = sending data via serial port to PC, 0 = don't send data */
#define SEND_GYRO_DATA_TO_USART	0		/* 1 = sending data via serial port to PC, 0 = don't send data */
#define MOTOR_OFF	0					/* 1 = motors always off, 0 = motors controlled by tControl.c */

/* Variables -----------------------------------------------------------------*/
typedef struct {
	int16_t	AccelX, AccelY, AccelZ;
	int16_t	GyroX, GyroY, GyroZ;
  } xIMUDATA_t;

typedef struct {
  	uint16_t	Motor1, Motor2;
  } xMotorPWMCommand_t;




#endif /* DVARIABLES_H_ */
