#include "Serial.h"

typedef struct SerialStruct
{
	char rxBuffer[SERIAL_RX_BUFFER_SIZE];
	char txBuffer[SERIAL_TX_BUFFER_SIZE];
    char command[SERIAL_RX_BUFFER_SIZE];
} SerialStruct;

static const char helpCommand[] = "help";

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

Status Serial_Handler(Serial *pSelf)
{
    if (pSelf == NULL)
    {
        return INVALID_PARAMETERS;
    }

    // Get command from input UART buffer
    Status status = Serial_ReceiveCmd(pSelf);

    if (status != OK)
    {
        return status;
    }

    // Handle command from buffer
    if (strstr(pSelf->command, helpCommand) == NULL)
    {
        return UNSUPPORTED;
    }

    status = Serial_SendResponse(pSelf, HELP_OUTPUT);
    return status;

}