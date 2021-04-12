// SerialSpy.c
#include "SerialSpy.h"

typedef struct SerialStruct
{
	char rxBuffer[SERIAL_RX_BUFFER_SIZE];
	char txBuffer[SERIAL_TX_BUFFER_SIZE];
} SerialStruct;

Status SerialSpy_SetRxBuffer(Serial *pSelf, char* pData, uint32_t len) 
{

}

Status SerialSpy_GetTxBuffer(Serial *pSelf, char** pData) 
{

}