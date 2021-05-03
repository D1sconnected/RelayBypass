#include "GpioSpy.h"

bool aBtnState = true;
bool bBtnState = true;

static Node *pGpioList = NULL;

EmulatedGpioStatesStruct emulatedGpio = {0};

Status USER_GPIO_PushCommand(StateStruct *pCmd)
{
	if (pCmd == NULL) 
	{
		return INVALID_PARAMETERS;
	}

	List_PushBack(&pGpioList, *pCmd);

	return OK;
}

Status USER_GPIO_HandOverLocalList(Node **pMasterList)
{
	StateStruct temp;

	if (pGpioList == NULL)
	{
		return NO_NEW_COMMANDS;
	}

	while (pGpioList != NULL)
	{
	temp = List_Pop(&pGpioList);
	List_PushBack(pMasterList, temp);
	}

	return OK;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if ((GPIO_Pin & (A_BTN_Pin | B_BTN_Pin)) && ((aBtnState == true) || (bBtnState == true)))
	{
		HAL_TIM_Base_Start_IT(&htim2);
		
		if (GPIO_Pin & A_BTN_Pin) 
		{
			aBtnState = false;
		}

		else if (GPIO_Pin & B_BTN_Pin)
		{
			bBtnState = false;
		}
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

	else if (GPIO_Pin == A_CODE_0_Pin)
	{
		return emulatedGpio.codeA0;
	}

	else if (GPIO_Pin == A_CODE_1_Pin)
	{
		return emulatedGpio.codeA1;
	}

	else if (GPIO_Pin == B_CODE_0_Pin)
	{
		return emulatedGpio.codeB0;
	}

	else if (GPIO_Pin == B_CODE_1_Pin)
	{
		return emulatedGpio.codeB1;
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