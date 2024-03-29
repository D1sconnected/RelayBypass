// TimSpy.h
#ifndef TIMSPY_HEADER_FILE_H
#define TIMSPY_HEADER_FILE_H

#ifdef MIMIC_F1
#include "../../../Firmware/RelayBypass_Mimic_STM32F101C4/Core/Inc/tim.h"
#endif

#ifdef CONSTRUCTOR_F1
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/tim.h"
#endif

#ifdef CONSTRUCTOR_L1
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/tim.h"
#endif

#include "../../../SharedLibs/RelayBypass/Include/Button.h"

HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *pHtim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *pHtim);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
