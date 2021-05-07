// TimSpy.h
#ifndef TIMSPY_HEADER_FILE_H
#define TIMSPY_HEADER_FILE_H

#include "tim.h"

HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *pHtim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *pHtim);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
