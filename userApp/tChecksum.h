/*
 * tChecksum.h
 *
 *  Created on: Nov 10, 2017
 *      Author: root
 */

#ifndef TCHECKSUM_H_
#define TCHECKSUM_H_

void Checksum_init(unsigned short ply);
unsigned short Checksum_update(void* msg, short length, unsigned short crc);
unsigned short Checksum_publish(unsigned short crc);
char Checksum_isValid(void* msg, short length);


#endif /* TCHECKSUM_H_ */
