// SerialSpy.h
#ifndef SERIALSPY_HEADER_FILE_H
#define SERIALSPY_HEADER_FILE_H

#include "Common.h"

#define SERIAL_RX_BUFFER_SIZE
#define SERIAL_TX_BUFFER_SIZE

Status SerialSpy_SetRxBuffer(Serial *pSelf, char *pData , uint32_t len);
Status SerialSpy_GetTxBuffer(Serial *pSelf, char **pData);

#endif