/*
 * d_LSM6DS3.h
 *
 * This file contains the register define of the LSM6DS3 IMU chip from STMicroelectronics. This file
 * is based on the datasheet LSM6DS3 rev: DocID026899 Rev 8 / FEB 2016.
 * Note: not all device registers are implemented here. For all registers and full description
 * see the datasheet
 *
 *  Created on: 05.09.2017
 *      Author: mac
 */

#ifndef D_LSM6DS3_H_
#define D_LSM6DS3_H_

#define LSM6DS2_ADRESS  (0x6A <<1)  //Address of the IMU, bitshifted to make space to take the r/w bit



/************** Device Registers  *******************/
#define LSM6DS3_FUNC_CFG_ACCESS		0x01	/* enables access to embedded function registers 0x02 to 0x32*/
#define LSM6DS3_ORIENT_CFG_G 		0x0B	/* orientation of accel and gyro*/
#define LSM6DS3_INT1_CTRL 			0x0D	/* interrupt ctrl regiter */
#define LSM6DS3_WHO_AM_I 			0x0F	/* read only, returns 0x69*/
#define LSM6DS3_CTRL1_XL 			0x10	/* accl ctrl register */
#define LSM6DS3_CTRL2_G  			0X11	/* gyro ctrl register */
#define LSM6DS3_CTRL3_C  			0X12	/* common ctrl register */
#define LSM6DS3_CTRL4_C  			0X13	/* interrupt ctrl register */
#define LSM6DS3_CTRL5_C  			0X14	/* measurements rounding and self test */
#define LSM6DS3_CTRL7_G  			0X16	/* Gyro rate ctrl register */
#define LSM6DS3_TAP_SRC   			0X1C	/* tap source register */
#define LSM6DS3_STATUS_REG 			0X1E	/* new data available */
#define LSM6DS3_OUTX_L_G 			0X22	/* x-axis gyro output, LSB side: D7...D0*/
#define LSM6DS3_OUTX_H_G 			0X23	/* x-axis gyro output, MSB side: D15...D8*/
#define LSM6DS3_OUTY_L_G 			0X24	/* y-axis gyro output, LSB side: D7...D0*/
#define LSM6DS3_OUTY_H_G 			0X25	/* y-axis gyro output, MSB side: D15...D8*/
#define LSM6DS3_OUTZ_L_G 			0X26	/* z-axis gyro output, LSB side: D7...D0*/
#define LSM6DS3_OUTZ_H_G 			0X27	/* z-axis gyro output, MSB side: D15...D8*/
#define LSM6DS3_OUTX_L_XL 			0X28	/* x-axis accel output, LSB side: D7...D0*/
#define LSM6DS3_OUTX_H_XL 			0X29	/* x-axis accel output, MSB side: D15...D8*/
#define LSM6DS3_OUTY_L_XL 			0X2A	/* y-axis accel output, LSB side: D7...D0*/
#define LSM6DS3_OUTY_H_XL 			0X2B	/* y-axis accel output, MSB side: D15...D8*/
#define LSM6DS3_OUTZ_L_XL 			0X2C	/* z-axis accel output, LSB side: D7...D0*/
#define LSM6DS3_OUTZ_H_XL 			0X2D	/* z-axis accel output, MSB side: D15...D8*/
#define LSM6DS3_TAP_CFG 			0X58	/* timestamp, pedometer, filterring, tap*/




/************** Registers Bit Masks  *******************/
/* FUNC_CFG_ACCESS (0x01) register bit mask */
#define LSM6DS3_FUNC_CFG		0x80	/* enables access to embedded function registers 0x02 to 0x32*/

/* Register ORIENT_CFG_G (0Bh) register bit mask */
#define LSM6DS3_SignX_G		0x20	/* Gyro X-Axis, 0 = default rotation, 1 = inverse rotation */
#define LSM6DS3_SignY_G		0x10	/* Gyro Y-Axis, 0 = default rotation, 1 = inverse rotation */
#define LSM6DS3_SignZ_G		0x08	/* Gyro Z-Axis, 0 = default rotation, 1 = inverse rotation */

/* Register INT1_CTRL (0Dh) register bit mask */
#define LESM6DS3_INT1_DRDY_G  0x02	/* Gyroscope Data Ready on INT1 pad. Default value: 0 */

/* Register CTRL1_XL (10h)  register bit mask */
/* Accelerometer output data rate (ODRXL) selection. Default value: ODR_OFF */
#define LSM6D3_ODRXL_OFF	0x00
#define LSM6D3_ODRXL_12HZ	0x10
#define LSM6D3_ODRXL_26HZ	0x20
#define LSM6D3_ODRXL_52HZ	0x30
#define LSM6D3_ODRXL_104HZ	0x40
#define LSM6D3_ODRXL_208HZ	0x50
#define LSM6D3_ODRXL_416HZ	0x60
#define LSM6D3_ODRXL_844HZ	0x70
#define LSM6D3_ODRXL_1660HZ	0x80
/*Accelerometer full-scale selection. Default value: +-2g.*/
#define LSM6DS3_FSXL_2G		0x00	/* max: 2g, 30.5 mg / LSB */
#define LSM6DS3_FSXL_4G		0x08	/* max: 4g, 61 mg / LSB */
#define LSM6DS3_FSXL_8G		0x0C	/* max: 8g, 122 mg / LSB */
#define LSM6DS3_FSXL_16G	0x04	/* max: 16g, 244 mg / LSB */
/*Anti-aliasing filter bandwidth selection. Default value: 400 Hz*/
#define LSM6DS_BWXL_50HZ	0x03
#define LSM6DS_BWXL_100HZ	0x02
#define LSM6DS_BWXL_200HZ	0x01
#define LSM6DS_BWXL_400HZ	0x00

/* Register CTRL2_G (11h)  register bit mask */
/* Gyroscope output data rate (ODRG) selection. Default value: ODR_OFF */
#define LSM6D3_ODRG_OFF		0x00
#define LSM6D3_ODRG_12HZ	0x10
#define LSM6D3_ODRG_26HZ	0x20
#define LSM6D3_ODRG_52HZ	0x30
#define LSM6D3_ODRG_104HZ	0x40
#define LSM6D3_ODRG_208HZ	0x50
#define LSM6D3_ODRG_416HZ	0x60
#define LSM6D3_ODRG_833HZ	0x70
#define LSM6D3_ODRG_1660HZ	0x80
/* Gyroscope full-scale (FSG) selection. Default value: 245°/s */
#define LSM6D3_FSG_125DPS	0x02	/* max: 125°/s, 4.375 mdps/LSB */
#define LSM6D3_FSG_245DPS	0x00	/* max: 245°/s, 8.75 mdps/LSB */
#define LSM6D3_FSG_500DPS	0x04	/* max: 500°/s, 17.5 mdps/LSB */
#define LSM6D3_FSG_1000DPS	0x08	/* max: 1000°/s, 35 mdps/LSB */
#define LSM6D3_FSG_2000DPS	0x0C	/* max: 2000°/s, 70 mdps/LSB */

/* Register STATUS_REG (0X1E) register bit mask */
#define LSM6DS3_GDA 		0X02	/* new gyro data, 1 = available */







#endif /* D_LSM6DS3_H_ */
