/*
 * tGyro.h
 *
 * Gyro task header file
 *
 *  Created on: 05.09.2017
 *      Author: mac
 */



#ifndef TGYRO_H_
#define TGYRO_H_

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"
#include "i2c.h"
#include "usart.h"

#include "dLSM6DS3.h"	/*LSM6DS3 driver data*/
#include "../userApp/dVariables.h"



/* Variables -----------------------------------------------------------------*/
extern osMessageQId GyrodataQueueHandle;



/* Function prototypes -------------------------------------------------------*/
void vtGyroStartTask(void const * argument);
void vGyroInitLSMD6DS3 (void);
void vReadIMU(I2C_HandleTypeDef *pxI2CHandler, int16_t *pxDataValue, uint8_t I2C_HByte, uint8_t I2C_LByte);

#endif /* T
GYRO_H_ */
