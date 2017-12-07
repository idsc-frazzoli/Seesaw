/*
 * tGyro.c
 *
 * Gyro task source file
 *
 *  Created on: 05.09.2017
 *      Author: mac
 */


/* Includes ------------------------------------------------------------------*/
#include "tGyro.h"




/* vtGyroStartTask function */
void vtGyroStartTask(void const * argument)
{
	/* local variables -------------------------------------------------- */
	xIMUDATA_t xIMUReceiveBuffer;

	/*IMU initialisation */
	vGyroInitLSMD6DS3();

	 while(1)
	  {
		 /* read data from IMU */
		 vReadIMU(&hi2c1, &xIMUReceiveBuffer.AccelX, LSM6DS3_OUTX_H_XL, LSM6DS3_OUTX_L_XL);
//		 vReadIMU(&hi2c1, &xIMUReceiveBuffer.AccelY, LSM6DS3_OUTY_H_XL, LSM6DS3_OUTY_L_XL);
//		 vReadIMU(&hi2c1, &xIMUReceiveBuffer.AccelZ, LSM6DS3_OUTZ_H_XL, LSM6DS3_OUTZ_L_XL);
//		 vReadIMU(&hi2c1, &xIMUReceiveBuffer.GyroX, LSM6DS3_OUTX_H_G, LSM6DS3_OUTX_L_G);
		 vReadIMU(&hi2c1, &xIMUReceiveBuffer.GyroY, LSM6DS3_OUTY_H_G, LSM6DS3_OUTY_L_G);
//		 vReadIMU(&hi2c1, &xIMUReceiveBuffer.GyroZ, LSM6DS3_OUTZ_H_G, LSM6DS3_OUTZ_L_G);

		 /* send data to Queue */
	     osMailPut(GyrodataQueueHandle, &xIMUReceiveBuffer);

	     /* Delay to slow down this task. FixMe: change IMU readout to be controlled by interrupt */
	     osDelay(5);
	  }
}

/* Thins functions initialises the IMU. See dLSM6DS3.h for register explanations*/
void vGyroInitLSMD6DS3 (void)
{
	uint8_t uiI2C_Data[2];

	/* Init gyroscope */
	/* ODRG = Gyroscope output data rate selection. Default value: ODR_OFF */
	/* FSG = Gyroscope full-scale selection. Default value: 245�/s */
	uiI2C_Data[0] = LSM6DS3_CTRL2_G;
	uiI2C_Data[1] = (LSM6D3_ODRG_104HZ | LSM6D3_FSG_245DPS);
	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t) (LSM6DS2_ADRESS), (uint8_t *) uiI2C_Data, 0x02, 100);

	/* Init accelerometer */
	/* ODRXL = output data rate selection. Default value: ODR_OFF */
	/* FSXL =  full-scale selection. Default value: +-2g. */
	/* BWXL = Anti-aliasing filter bandwidth selection. Default value: 400 Hz*/
	uiI2C_Data[0] = LSM6DS3_CTRL1_XL;
	uiI2C_Data[1] = (LSM6D3_ODRXL_104HZ | LSM6DS3_FSXL_2G | LSM6DS_BWXL_100HZ);
	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t) (LSM6DS2_ADRESS), (uint8_t *) uiI2C_Data, 0x02, 100);
}


/*
 * This function reads the IMU on the I2C, converts the two 8bit values (high and
 * low side of one 16bit value) into a 16bit value and writes the 16bit back
 * into the IMU data structure.
 */
void vReadIMU(I2C_HandleTypeDef *pxI2CHandler, int16_t *pxDataValue, uint8_t I2C_HByte, uint8_t I2C_LByte)
{
	uint8_t isOk = 1;
	HAL_StatusTypeDef status;
	uint8_t pcData;
	int16_t data;

	status = HAL_I2C_Mem_Read(pxI2CHandler, LSM6DS2_ADRESS, I2C_HByte , 0x01, &pcData, 0x01, 100);
	isOk &= status == HAL_OK;
	data = pcData << 8;
	status = HAL_I2C_Mem_Read(pxI2CHandler, LSM6DS2_ADRESS, I2C_LByte , 0x01, &pcData, 0x01, 100);
	isOk &= status == HAL_OK;
	data |= pcData;
	if (isOk)
	  *pxDataValue = data;
}





