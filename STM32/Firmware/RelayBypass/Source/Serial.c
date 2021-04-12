#include "Serial.h"

typedef struct SerialStruct
{
	char rxBuffer[SERIAL_RX_BUFFER_SIZE];
	char txBuffer[SERIAL_TX_BUFFER_SIZE];
} SerialStruct;

Serial *Serial_Create(void)
{
	Serial *pSelf = (Serial*)calloc(1, sizeof(SerialStruct));
	return pSelf;
}

void Serial_Destroy(Serial *pSelf)
{
	if (pSelf == NULL)
	{
		return;
	}

	free(pSelf);
	pSelf = NULL;
}
