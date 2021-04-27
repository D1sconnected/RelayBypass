#include "TimSpy.h"

TIM_HandleTypeDef htim2;

extern bool aBtnState;
extern bool bBtnState;

static Node* pLocalTimList = NULL;

Status USER_TIM_PushCommand(StateStruct* pCmd)
{
	if (pCmd == NULL)
	{
		return INVALID_PARAMETERS;
	}

	List_PushBack(&pLocalTimList, *pCmd);

	return OK;
}

Status USER_TIM_HandOverLocalList(Node** pMasterList)
{
	StateStruct temp;

	if (pLocalTimList == NULL)
	{
		return NO_NEW_COMMANDS;
	}

	while (pLocalTimList != NULL)
	{
		temp = List_Pop(&pLocalTimList);
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

	if (HAL_GPIO_ReadPin(A_BTN_GPIO_Port, A_BTN_Pin) == GPIO_PIN_RESET)
	{
		cmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
		cmdBlock.channel = CHANNEL_A;
		cmdBlock.specificator = NULL;
		Status status = USER_TIM_PushCommand(&cmdBlock);
		aBtnState = true;
	}

	else if (HAL_GPIO_ReadPin(B_BTN_GPIO_Port, B_BTN_Pin) == GPIO_PIN_RESET)
	{
		cmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
		cmdBlock.channel = CHANNEL_B;
		cmdBlock.specificator = NULL;
		Status status = USER_TIM_PushCommand(&cmdBlock);
		bBtnState = true;
	}
	HAL_TIM_Base_Stop_IT(&htim2);
}
