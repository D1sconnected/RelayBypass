// SerialSpy.c
#include "SerialSpy.h"

typedef struct SerialStruct
{
	char rxBuffer[SERIAL_RX_BUFFER_SIZE];
	char txBuffer[SERIAL_TX_BUFFER_SIZE];
	char command[SERIAL_RX_BUFFER_SIZE];
} SerialStruct;

Status SerialSpy_SetRxBuffer(Serial *pSelf, char *pData, uint32_t len) 
{
	if (pSelf == NULL || pData == NULL)
	{
		return INVALID_PARAMETERS;
	}

	if (len > SERIAL_RX_BUFFER_SIZE) 
	{
		return OUT_OF_BOUNDS;
	}

	memcpy(pSelf->rxBuffer, pData, len);
	return OK;
}

Status SerialSpy_GetTxBuffer(Serial *pSelf, char **pData) 
{
	if (pSelf == NULL || pData == NULL)
	{
		return INVALID_PARAMETERS;
	}

	*pData = pSelf->txBuffer;
	return OK;
}

Status Serial_ReceiveCmd(Serial* pSelf, char* pCommand)
{
	return;
}

Status Serial_SendResponse(Serial* pSelf, char* pCommand)
{
	return;
}