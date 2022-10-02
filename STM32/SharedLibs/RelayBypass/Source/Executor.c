#include "../Include/Executor.h"

Executor * Executor_Create(void)
{
    Executor *pSelf = (Executor*)calloc(1, sizeof(Executor));
    pSelf->pExecutorList = NULL;
    return pSelf;
}

void Executor_Destroy(Executor *pSelf)
{
    if (pSelf == NULL)
    {
        return;
    }

    free(pSelf);
    pSelf = NULL;
}

Status Executor_PushCommand(Executor *pSelf, StateStruct* pCmd)
{
    if (pSelf == NULL || pCmd == NULL)
    {
        return INVALID_PARAMETERS;
    }

    List_PushBack(&pSelf->pExecutorList, *pCmd);

    return OK;
}

Status Executor_Handler(Executor *pSelf) 
{
    if (pSelf == NULL)
    {
        return INVALID_PARAMETERS;
    }

    ExecutorState state = EXECUTOR_STATE_IDLE;
    StateStruct currentCmdBlock = {0};
    Status status = Executor_UpdateList(pSelf);

    if (status != OK)
    {
        return status;
    }

    currentCmdBlock = List_Pop(&pSelf->pExecutorList);
    state = currentCmdBlock.state;

    switch (state) 
    {
        case EXECUTOR_STATE_IDLE:
        {
            return NO_COMMAND;
        }
        break;

        case EXECUTOR_STATE_SWITCH_CHANNEL:
        {
            status = Interface_SwitchChannel(currentCmdBlock.channel);
            return status;
        }
        break;

        case EXECUTOR_STATE_CHANGE_ROUTE:
        {
            status = Interface_ChangeRoute(currentCmdBlock.channel);
            return status;
        }
        break;

        case EXECUTOR_STATE_SAVE_ROUTE:
        {
            return UNSUPPORTED;
        }
        break;

        case EXECUTOR_STATE_TOGGLE_CHANNEL:
        {
            status = Interface_ToggleChannel(currentCmdBlock.channel);
            return status;
        }
        break;

        case EXECUTOR_STATE_TOGGLE_FOR_CONFIG_MODE:
        {
            status = Interface_ToggleForConfigMode();
            return status;
        }
        break;

        case EXECUTOR_STATE_GET_CHANNEL:
        {
            return UNSUPPORTED;
        }
        break;

        case EXECUTOR_STATE_TRACE_TO_MICROSD:
        {
            return UNSUPPORTED;
        }
        break;

        case EXECUTOR_STATE_TRACE_TO_UART:
        {
            return UNSUPPORTED;
        }
        break;

        case EXECUTOR_STATE_GET_UART_RX:
        {
            return UNSUPPORTED;
        }
        break;

        case EXECUTOR_STATE_SEND_UART_TX:
        {
            return UNSUPPORTED;
        }
        break;

        case EXECUTOR_STATE_WRITE_TO_DISPLAY:
        {
            return UNSUPPORTED;
        }
        break;

        case EXECUTOR_STATE_UPDATE_TAP_ON_CHANNEL:
        {
            if (currentCmdBlock.channel == CHANNEL_A)
            {
                gTapLedA = (uint16_t)((float)currentCmdBlock.number); // Reset global led indicator
            }
            else
            {
                gTapLedB = (uint16_t)((float)currentCmdBlock.number); // Reset global led indicator
            }

            status = Interface_UpdateTap(currentCmdBlock.channel, currentCmdBlock.number);
            return status;
        }
        break;

        case EXECUTOR_STATE_SWITCH_PROGRAM:
        {
            status = Interface_SwitchProgram(currentCmdBlock.channel, currentCmdBlock.specificator);
            return status;
        }
        break;

        case EXECUTOR_STATE_SWITCH_I2C_EEPROM:
        {
            status = Interface_SwitchEeprom(currentCmdBlock.channel);
            return status;
        }
        break;

        case EXECUTOR_STATE_UPDATE_DIGITAL_POT_BY_ADC:
        {
            float adcCoef = 4.096;

            if (currentCmdBlock.channel == CHANNEL_A)
            {
                gTapLedA = (uint16_t)((float)currentCmdBlock.number/adcCoef); // Reset global led indicator
            }
            else
            {
                gTapLedB = (uint16_t)((float)currentCmdBlock.number/adcCoef); // Reset global led indicator
            }

            status = Interface_UpdateDigitalPot(currentCmdBlock.channel, (uint8_t)(currentCmdBlock.number / 16));
            return status;
        }

        case EXECUTOR_STATE_UPDATE_MAX_TIME_FOR_TAP:
        {
            status = Interface_UpdateMaxTimeForTap(currentCmdBlock.channel, currentCmdBlock.specificator);
            return status;
        }
    }

     return NO_COMMAND;
}

Status Executor_UpdateList(Executor *pSelf)
{
    if (pSelf == NULL)
    {
        return INVALID_PARAMETERS;
    }

    // Call HandOverLocalList for each peripheral
    Status status = OK;
    status += Button_HandOverLocalList(&pSelf->pExecutorList);
    status += Timer_HandOverLocalList(&pSelf->pExecutorList);

    return status;
}
