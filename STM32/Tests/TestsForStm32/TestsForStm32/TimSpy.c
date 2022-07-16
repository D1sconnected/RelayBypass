#include "TimSpy.h"

TIM_HandleTypeDef htim2;
static Node *pTimList = NULL;

HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *pHtim) 
{
	return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *pHtim) 
{
	return HAL_OK;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    StateStruct cmdBlock = { 0 };

    static uint8_t changeRouteCounter = 0;
    static char changeRouteChannel = CHANNEL_A;

    GPIO_PinState gpioBtnStateA = HAL_GPIO_ReadPin(A_BTN_GPIO_Port, A_BTN_Pin);
    GPIO_PinState gpioBtnStateB = HAL_GPIO_ReadPin(B_BTN_GPIO_Port, B_BTN_Pin);
    GPIO_PinState gpioSwStateA1 = HAL_GPIO_ReadPin(A_SW_1_EXTI_GPIO_Port, A_SW_1_EXTI_Pin);
    GPIO_PinState gpioSwStateA3 = HAL_GPIO_ReadPin(A_SW_3_EXTI_GPIO_Port, A_SW_3_EXTI_Pin);
    GPIO_PinState gpioSwStateB1 = HAL_GPIO_ReadPin(B_SW_1_EXTI_GPIO_Port, B_SW_1_EXTI_Pin);
    GPIO_PinState gpioSwStateB3 = HAL_GPIO_ReadPin(B_SW_3_EXTI_GPIO_Port, B_SW_3_EXTI_Pin);

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

    if (gpioSwStateA1 == GPIO_PIN_RESET && gSwStateA1 == true)
    {
        cmdBlock.state = EXECUTOR_STATE_SWITCH_PROGRAM;
        cmdBlock.channel = CHANNEL_A;
        cmdBlock.specificator = UP;
        Status status = Timer_PushCommand(&cmdBlock);
        gSwStateA1 = false;
    }

    if (gpioSwStateA3 == GPIO_PIN_RESET && gSwStateA3 == true)
    {
        cmdBlock.state = EXECUTOR_STATE_SWITCH_PROGRAM;
        cmdBlock.channel = CHANNEL_A;
        cmdBlock.specificator = DOWN;
        Status status = Timer_PushCommand(&cmdBlock);
        gSwStateA3 = false;
    }

    if (gpioSwStateB1 == GPIO_PIN_RESET && gSwStateB1 == true)
    {
        cmdBlock.state = EXECUTOR_STATE_SWITCH_PROGRAM;
        cmdBlock.channel = CHANNEL_B;
        cmdBlock.specificator = UP;
        Status status = Timer_PushCommand(&cmdBlock);
        gSwStateB1 = false;
    }

    if (gpioSwStateB3 == GPIO_PIN_RESET && gSwStateB3 == true)
    {
        cmdBlock.state = EXECUTOR_STATE_SWITCH_PROGRAM;
        cmdBlock.channel = CHANNEL_B;
        cmdBlock.specificator = DOWN;
        Status status = Timer_PushCommand(&cmdBlock);
        gSwStateB3 = false;
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
