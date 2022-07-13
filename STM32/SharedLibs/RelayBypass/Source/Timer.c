#include "../Include/Timer.h"

static Node* pLocalTimList = NULL;

Status Timer_PushCommand(StateStruct* pCmd)
{
    if (pCmd == NULL)
    {
        return INVALID_PARAMETERS;
    }

    List_PushBack(&pLocalTimList, *pCmd);

    return OK;
}

Status Timer_HandOverLocalList(Node** pMasterList)
{
    if (pMasterList == NULL)
    {
        return INVALID_PARAMETERS;
    }

    StateStruct temp;

    while (pLocalTimList != NULL)
    {
        temp = List_Pop(&pLocalTimList);
        List_PushBack(pMasterList, temp);
    }

    return OK;
}

void Timer_Callback (TIM_HandleTypeDef *htim)
{
    StateStruct cmdBlock = { 0 };

    static uint8_t changeRouteCounter = 0;
    static char changeRouteChannel = CHANNEL_A;

    GPIO_PinState gpioBtnStateA = HAL_GPIO_ReadPin(A_BTN_GPIO_Port, A_BTN_Pin);
    GPIO_PinState gpioBtnStateB = HAL_GPIO_ReadPin(B_BTN_GPIO_Port, B_BTN_Pin);

    if (gpioBtnStateA == GPIO_PIN_RESET && gpioBtnStateB == GPIO_PIN_RESET)
    {
        changeRouteCounter++;
    }

    if (gpioBtnStateA == GPIO_PIN_RESET && gBtnStateA == true)
    {
        cmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
        cmdBlock.channel = CHANNEL_A;
        cmdBlock.specificator = 0;
        Status status = Timer_PushCommand(&cmdBlock);
        gBtnStateA = false;
    }

    if (gpioBtnStateB == GPIO_PIN_RESET && gBtnStateB == true)
    {
        cmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
        cmdBlock.channel = CHANNEL_B;
        cmdBlock.specificator = 0;
        Status status = Timer_PushCommand(&cmdBlock);
        gBtnStateB = false;
    }

    if (changeRouteCounter == COUNTS_FOR_CHANGE_ROUTE)
    {
        if (changeRouteChannel == CHANNEL_B)
        {
            changeRouteChannel = CHANNEL_A;
        }

        else if (changeRouteChannel == CHANNEL_A)
        {
            changeRouteChannel = CHANNEL_B;
        }

        //HAL_GPIO_TogglePin(MCU_PROG_GPIO_Port, MCU_PROG_Pin);

        cmdBlock.state = EXECUTOR_STATE_CHANGE_ROUTE;
        cmdBlock.channel = changeRouteChannel;
        cmdBlock.specificator = 0;
        Status status = Timer_PushCommand(&cmdBlock);
        changeRouteCounter = 0;

        cmdBlock.state = EXECUTOR_STATE_TOGGLE_CHANNEL;
        cmdBlock.channel = changeRouteChannel;
        cmdBlock.specificator = 0;
        status = Timer_PushCommand(&cmdBlock);
    }
}
