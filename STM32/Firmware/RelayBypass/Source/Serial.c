#include "Serial.h"

typedef struct SerialStruct
{
	char rxBuffer[SERIAL_RX_BUFFER_SIZE];
	char txBuffer[SERIAL_TX_BUFFER_SIZE];
    char command[SERIAL_RX_BUFFER_SIZE];
} SerialStruct;

static const char helpCommand[] = "help";
static const char toggleCommand[] = "toggle";

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
    if (strstr(pSelf->command, helpCommand) != NULL)
    {
        return Serial_HandleHelpCommand(pSelf);
    }

    else if (strstr(pSelf->command, toggleCommand) != NULL)
    {
        return Serial_HandleToggleCommand(pSelf);
    }

    return status;
}

Status Serial_HandleHelpCommand(Serial *pSelf)
{
    if (pSelf == NULL)
    {
        return INVALID_PARAMETERS;
    }

    Status status = Serial_SendResponse(pSelf, HELP_OUTPUT);
    return status;
}

Status Serial_HandleToggleCommand(Serial* pSelf)
{
    if (pSelf == NULL)
    {
        return INVALID_PARAMETERS;
    }

    if (pSelf->command[7] == 'A' ||
        pSelf->command[7] == 'a' ||
        pSelf->command[7] == 'B' ||
        pSelf->command[7] == 'b') 
        {
            if (pSelf->command[9] > 0) 
            {
                char toggleResponse[64] = { 0 };
                //toggleResponse = "Toggle Slot X x times\r\n";
                memcpy(toggleResponse, "Toggle Slot A 3 times\r\n", sizeof("Toggle Slot A 3 times\r\n"));
                toggleResponse[12] = pSelf->command[7];
                toggleResponse[14] = pSelf->command[9];
                
                return Serial_SendResponse(pSelf, toggleResponse);
            }
        }

    return INVALID_FORMAT;
}