// Serial.h
#ifndef SERIAL_HEADER_FILE_H
#define SERIAL_HEADER_FILE_H

#include "Common.h"

#define SERIAL_RX_BUFFER_SIZE	32
#define SERIAL_TX_BUFFER_SIZE	256

typedef struct SerialStruct Serial;

Serial *Serial_Create(void);

void Serial_Destroy(Serial* pSelf);

#endif