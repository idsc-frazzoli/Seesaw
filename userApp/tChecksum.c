/*
 * tChecksum.c
 *
 *  Created on: Nov 10, 2017
 *      Author: root
 */




// depending on the requirements: speed vs. memory
// the application can choose to use the fast table lookup
// of perform the computation when needed
// CRC = crc = "cyclic redundancy check"
#define CHECKSUM_LOOKUP   // comment or uncomment this line as needed
// ---
#ifdef CHECKSUM_LOOKUP
#define CHECKSUM_SIZE   256
unsigned short checksum_lookup[CHECKSUM_SIZE];
#else
unsigned short checksum_ply = 0x8005; // only default value, can be set by init
#endif

void Checksum_init(unsigned short ply) {
#ifdef CHECKSUM_LOOKUP
  unsigned char phi = ply >> 8;
  unsigned char ctr[8];
  unsigned char c0;
  unsigned char top;
  unsigned short crc;
  unsigned short c1;
  for (c1 = 0; c1 < CHECKSUM_SIZE; ++c1) {
    top = c1;
    for (c0 = 0; c0 < 8; ++c0)
      if (top & 0x80) { // Check top bit of the register
        top = ((top << 1) & 0xFE) ^ phi;
        ctr[c0] = 1;
      } else {
        top <<= 1;
        ctr[c0] = 0;
      }
    crc = 0;
    for (c0 = 0; c0 < 8; ++c0)
      if (ctr[c0]) // if the control bit is one
        crc ^= ply << (7 - c0);
    checksum_lookup[c1] = crc;
  }
#else
  checksum_ply = ply;
#endif
}

// private function (only visible to checksum.c)
unsigned short Checksum_rotate(unsigned short crc, unsigned char value) {
#ifdef CHECKSUM_LOOKUP
  return ((crc << 8) + value) ^ checksum_lookup[(crc >> 8) & 0xFF];
#else
  // this is the 'slower' computation, keep as memory efficient alternative:
  char l_c_c1;
  unsigned short l_us_top;
  for (l_c_c1 = 0; l_c_c1 < 8; l_c_c1++) {
    l_us_top = crc & 0x8000;
    crc = (crc << 1) + ((value >> (7 - l_c_c1)) & 1);
    if (l_us_top)
    crc ^= checksum_ply;
  }
  return crc;
#endif
}


unsigned short Checksum_update(void* msg, short length, unsigned short crc) {
  short count = 0;
  char* message = (char*) msg;
  for (count = 0; count < length; ++count)
    crc = Checksum_rotate(crc, message[count]);
  return crc;
}

//To be used to create the final CRC
unsigned short Checksum_publish(unsigned short crc) {
  crc = Checksum_rotate(crc, 0);
  crc = Checksum_rotate(crc, 0);
  return crc;
}

// parameter length includes 2 bytes of crc. If the result of checksum publish is 0, then checksum us valid (1)
char Checksum_isValid(void* msg, short length) {
  return 0 == Checksum_publish(Checksum_update(msg, length, 0)); //return 0 if invalid
}
