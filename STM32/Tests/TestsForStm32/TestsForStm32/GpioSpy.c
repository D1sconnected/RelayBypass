#include "GpioSpy.h"

bool aBtnState = true;
bool bBtnState = true;
static Node *pLocalList = NULL;

EmulatedGpioStatesStruct emulatedGpio;

Status USER_GPIO_PushCommand(StateStruct *pCmd)
{
	if (pCmd == NULL) 
	{
		return INVALID_PARAMETERS;
	}

	List_PushBack(&pLocalList, *pCmd);

	return OK;
}

Status USER_GPIO_HandOverLocalList(Node **pMasterList)
{
	StateStruct temp;

	if (pLocalList == NULL) 
	{
		return NO_NEW_COMMANDS;
	}

	while (pLocalList != NULL) 
	{
	temp = List_Pop(&pLocalList);
	List_PushBack(pMasterList, temp);
	}

	return OK;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if ((GPIO_Pin == (A_BTN_Pin | B_BTN_Pin)) && ((aBtnState == true) || (bBtnState == true)))
	{
		HAL_TIM_Base_Start_IT(&htim2);
		//
	}
}

GPIO_PinState HAL_GPIO_ReadPin(void *pGPIOx, uint16_t GPIO_Pin)
{
	if (GPIO_Pin == A_BTN_Pin) 
	{
		return emulatedGpio.buttonA;
	}

	else if (GPIO_Pin == B_BTN_Pin)
	{
		return emulatedGpio.buttonB;
	}
}

void HAL_GPIO_WritePin(void* pGPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) 
{
	return;
}

void HAL_GPIO_TogglePin(void* pGPIOx, uint16_t GPIO_Pin)
{
	return;
}

//ToDo: Place in different location
void HAL_Delay() 
{
	return;
}