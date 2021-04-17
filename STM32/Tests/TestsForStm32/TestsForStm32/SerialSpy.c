// SerialSpy.c
#include "SerialSpy.h"

typedef struct SerialStruct
{
	char rxBuffer[SERIAL_RX_BUFFER_SIZE];
	char txBuffer[SERIAL_TX_BUFFER_SIZE];
	char command[SERIAL_RX_BUFFER_SIZE];
} SerialStruct;

static bool IsEndOfString(char* buffer)
{
	for (int i = 0; i < SERIAL_RX_BUFFER_SIZE; i++)
	{
		if (buffer[i] == '\n')
		{
			return true;
		}
	}
	return false;
}

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

Status Serial_ReceiveCmd(Serial *pSelf)
{
	if (pSelf == NULL)
	{
		return INVALID_PARAMETERS;
	}
	// Check for data in buffer
	uint32_t commandLen = strlen(pSelf->rxBuffer);
	if (commandLen == 0)
	{
		return NO_DATA;
	}
	// Check for `\n`
	bool isEndOfString = IsEndOfString(pSelf->rxBuffer);
	if (isEndOfString == false)
	{
		return NO_DATA;
	}
	// Copy command to rxBuffer
	strncpy(pSelf->command, pSelf->rxBuffer, commandLen);
	pSelf->rxBuffer[SERIAL_RX_BUFFER_SIZE - 1] = 0;
	return OK;
}

Status Serial_SendResponse(Serial *pSelf, char *pCommand)
{
	if (pSelf == NULL || pCommand == NULL)
	{
		return INVALID_PARAMETERS;
	}
	// Check for data in buffer
	uint32_t commandLen = strlen(pCommand);
	if (commandLen > SERIAL_TX_BUFFER_SIZE)
	{
		return OUT_OF_BOUNDS;
	}
	// Copy command to txBuffer
	strncpy(pSelf->txBuffer, pCommand, commandLen);
	pSelf->txBuffer[SERIAL_TX_BUFFER_SIZE - 1] = 0;
	return OK;
}