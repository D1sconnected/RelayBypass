#include "../Include/Button.h"

bool gBtnStateA = false;
bool gBtnStateB = false;
bool gSwStateA1 = false;
bool gSwStateA3 = false;
bool gSwStateB1 = false;
bool gSwStateB3 = false;

static Node *pGpioList = NULL;

Status Button_PushCommand(StateStruct *pCmd)
{
    if (pCmd == NULL)
    {
        return INVALID_PARAMETERS;
    }

    List_PushBack(&pGpioList, *pCmd);

    return OK;
}

Status Button_HandOverLocalList(Node **pMasterList)
{
    if (pMasterList == NULL)
    {
        return INVALID_PARAMETERS;
    }

    StateStruct temp;

    while (pGpioList != NULL)
    {
    temp = List_Pop(&pGpioList);
    List_PushBack(pMasterList, temp);
    }

    return OK;
}

void Button_Callback (uint16_t GPIO_Pin)
{
    HAL_TIM_Base_Start_IT(&htim2);

    int gpioPin = GPIO_Pin & (A_BTN_Pin | B_BTN_Pin | A_SW_1_EXTI_Pin | A_SW_3_EXTI_Pin | B_SW_1_EXTI_Pin | B_SW_3_EXTI_Pin);
    bool gpioState = (gBtnStateA == false) || (gBtnStateB == false) || (gSwStateA1 == false) || (gSwStateA3 == false) || (gSwStateB1 == false) || (gSwStateB3 == false);

    if (gpioPin && gpioState)
    {
        if (GPIO_Pin & A_BTN_Pin)
        {
            gBtnStateA = true;
        }

        if (GPIO_Pin & B_BTN_Pin)
        {
            gBtnStateB = true;
        }

        if (GPIO_Pin & A_SW_1_EXTI_Pin)
        {
            gSwStateA1 = true;
        }

        if (GPIO_Pin & A_SW_3_EXTI_Pin)
        {
            gSwStateA3 = true;
        }

        if (GPIO_Pin & B_SW_1_EXTI_Pin)
        {
            gSwStateB1 = true;
        }

        if (GPIO_Pin & B_SW_3_EXTI_Pin)
        {
            gSwStateB3 = true;
        }
    }
}
