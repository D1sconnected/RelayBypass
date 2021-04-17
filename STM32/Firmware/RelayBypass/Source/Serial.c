#include "Serial.h"
#include "Interface.h"

typedef struct SerialStruct
{
	char rxBuffer[SERIAL_RX_BUFFER_SIZE];
	char txBuffer[SERIAL_TX_BUFFER_SIZE];
    char command[SERIAL_RX_BUFFER_SIZE];
} SerialStruct;

static const char helpCommand[] = "help";
static const char toggleCommand[] = "toggle";
static const char switchCommand[] = "switch";

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

    else if (strstr(pSelf->command, switchCommand) != NULL)
    {
        return Serial_HandleSwitchCommand(pSelf);
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

Status Serial_HandleToggleCommand(Serial *pSelf)
{
    if (pSelf == NULL)
    {
        return INVALID_PARAMETERS;
    }

    // Check if slot parameter is correct
    if (pSelf->command[7] == CHANNEL_A || pSelf->command[7] == CHANNEL_B) 
        {
            Status status = Interface_ToggleChannel(pSelf->command[7]);
            /*
            if (status != OK) 
            {
                return status;
            }
            */
            char toggleResponse[16] = {0};
            memcpy(toggleResponse, TOGGLE_OUTPUT, sizeof(TOGGLE_OUTPUT));
            toggleResponse[12] = pSelf->command[7];
            toggleResponse[13] = '\r';
            toggleResponse[14] = '\n';
                
            return Serial_SendResponse(pSelf, toggleResponse);
        }

    return INVALID_FORMAT;
}

Status Serial_HandleSwitchCommand(Serial *pSelf) 
{
    if (pSelf == NULL)
    {
        return INVALID_PARAMETERS;
    }

    // Check if slot parameter is correct
    if (pSelf->command[7] == CHANNEL_A || pSelf->command[7] == CHANNEL_B)
    {
        Status status = Interface_SwitchChannel(pSelf->command[7]);
        
        if (status != OK)
        {
            return status;
        }
        
        char switchResponse[16] = { 0 };
        memcpy(switchResponse, SWITCH_OUTPUT, sizeof(SWITCH_OUTPUT));
        switchResponse[12] = pSelf->command[7];
        switchResponse[13] = '\r';
        switchResponse[14] = '\n';

        return Serial_SendResponse(pSelf, switchResponse);
    }

    return INVALID_FORMAT;
}