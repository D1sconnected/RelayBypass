#include "TimSpy.h"

TIM_HandleTypeDef htim2;

HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *pHtim) 
{
	return HAL_OK;
}

/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *pHtim) 
{
	if (HAL_GPIO_ReadPin(Push_Button_GPIO_Port, Push_Button_Pin) == GPIO_PIN_RESET) 
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		state = true;
		HAL_TIM_Base_Stop_IT(&htim2);
	}
}
*/