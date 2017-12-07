/*
 * tDataTransmit.c
 *
 *  Created on: Nov 3, 2017
 *      Author: root
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "usart.h"
#include "tControl.h"
#include <string.h>
#include "tChecksum.h"

#define SEEDcrc 0x8005

#pragma pack(push, 1) // exact fit - no padding
struct dataPackage {
	uint32_t systemTime;
	struct signalPackage signals;
};
#pragma pack(pop) //back to whatever the previous packing mode was

void vtDataTransmitStartTask(void const * argument) {

	Checksum_init(SEEDcrc);

	struct dataPackage dataP;

	while (1) {
		/* LED heartbeat */
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
		osDelay(5);

		/* compile UART message */
		// current message identifier: 3x uInt8, 1x uInt32,  2x double: 8, 2 x uInt8  = 24
		uint32_t dataTLength = 33; /// CHANGE BOTH HERE AND BELOW!
		uint8_t uaBuffer[33];
		memset(uaBuffer, 0, dataTLength);

		/* message identifier */
		uaBuffer[0] = 'E';
		uaBuffer[1] = 'T';
		uaBuffer[2] = 'H';

		/* message body */
		dataP.systemTime = xTaskGetTickCount();
		while (inSignalWrite) {
		}
		dataP.signals = seeSig;
		memcpy(&uaBuffer[3], &dataP, sizeof(dataP));

		/* checksum */ //TODO
		unsigned short crc = 0;
		crc = Checksum_update(uaBuffer, (dataTLength - 2), crc);
		crc = Checksum_publish(crc);
		memcpy(&uaBuffer[3 + 4 + 8 + 8 + 8], &crc, sizeof(crc));

		/*send  UART message*/
		HAL_UART_Transmit(&huart2, (uint8_t*) uaBuffer, dataTLength, 0xFFFF);

	}
}

