#include "../Include/Button.h"

bool gBtnStateA = false;
bool gBtnStateB = false;

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
    if ((GPIO_Pin & (A_BTN_Pin | B_BTN_Pin)) && ((gBtnStateA == false) || (gBtnStateB == false)))
    {

        if (GPIO_Pin & A_BTN_Pin)
        {
            gBtnStateA = true;
        }

        if (GPIO_Pin & B_BTN_Pin)
        {
            gBtnStateB = true;
        }
    }
}
