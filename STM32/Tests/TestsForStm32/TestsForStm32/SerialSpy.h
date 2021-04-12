// SerialSpy.h
#ifndef SERIALSPY_HEADER_FILE_H
#define SERIALSPY_HEADER_FILE_H

#include "Common.h"
#include "Serial.h"

Status SerialSpy_SetRxBuffer(Serial *pSelf, char *pData , uint32_t len);
Status SerialSpy_GetTxBuffer(Serial *pSelf, char **pData);

#endif