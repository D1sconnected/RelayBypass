#include "TimSpy.h"

TIM_HandleTypeDef htim2;

extern bool aBtnState;
extern bool bBtnState;

static Node *pTimList = NULL;

Status USER_TIM_PushCommand(StateStruct* pCmd)
{
	if (pCmd == NULL)
	{
		return INVALID_PARAMETERS;
	}

	List_PushBack(&pTimList, *pCmd);

	return OK;
}

Status USER_TIM_HandOverLocalList(Node** pMasterList)
{
	if (pMasterList == NULL)
	{
		return INVALID_PARAMETERS;
	}

	StateStruct temp;

	while (pTimList != NULL)
	{
		temp = List_Pop(&pTimList);
		List_PushBack(pMasterList, temp);
	}

	return OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *pHtim) 
{
	return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *pHtim) 
{
	return HAL_OK;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    StateStruct cmdBlock = { 0 };

    static uint8_t changeRouteCounter = 0;
    static char changeRouteChannel = CHANNEL_A;

    GPIO_PinState aBtnGpioState = HAL_GPIO_ReadPin(A_BTN_GPIO_Port, A_BTN_Pin);
    GPIO_PinState bBtnGpioState = HAL_GPIO_ReadPin(B_BTN_GPIO_Port, B_BTN_Pin);

    if (aBtnGpioState == GPIO_PIN_RESET && bBtnGpioState == GPIO_PIN_RESET)
    {
        changeRouteCounter++;
    }

    if (aBtnGpioState == GPIO_PIN_RESET && aBtnState == true)
    {
        cmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
        cmdBlock.channel = CHANNEL_A;
        cmdBlock.specificator = 0;
        Status status = USER_TIM_PushCommand(&cmdBlock);
        aBtnState = false;
    }

    if (bBtnGpioState == GPIO_PIN_RESET && bBtnState == true)
    {
        cmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
        cmdBlock.channel = CHANNEL_B;
        cmdBlock.specificator = 0;
        Status status = USER_TIM_PushCommand(&cmdBlock);
        bBtnState = false;
    }

    if (changeRouteCounter == 100)
    {
        if (changeRouteChannel == CHANNEL_B)
        {
            changeRouteChannel = CHANNEL_A;
        }

        else if (changeRouteChannel == CHANNEL_A)
        {
            changeRouteChannel = CHANNEL_B;
        }

        HAL_GPIO_TogglePin(MCU_PROG_GPIO_Port, MCU_PROG_Pin);

        cmdBlock.state = EXECUTOR_STATE_CHANGE_ROUTE;
        cmdBlock.channel = changeRouteChannel;
        cmdBlock.specificator = 0;
        Status status = USER_TIM_PushCommand(&cmdBlock);
        changeRouteCounter = 0;

        cmdBlock.state = EXECUTOR_STATE_TOGGLE_CHANNEL;
        cmdBlock.channel = changeRouteChannel;
        cmdBlock.specificator = 0;
        status = USER_TIM_PushCommand(&cmdBlock);

    }

}
