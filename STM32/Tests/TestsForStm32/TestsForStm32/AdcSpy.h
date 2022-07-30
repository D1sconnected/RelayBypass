// AdcSpy.h
#ifndef ADCSPY_HEADER_FILE_H
#define ADCSPY_HEADER_FILE_H

#define ADC_SPY_GREEN_VALUE 3800
#define ADC_SPY_RED_VALUE   2500
#define ADC_SPY_BLUE_VALUE  1300

//#include "adc.h"
#include "Common.h"

#ifdef MIMIC_F1
#include "../../PlatformDependent/Mimic/Include/Interface_Mimic.h"
#include "../../../../Firmware/RelayBypass_Mimic_STM32F101C4/Core/Inc/adc.h"
#endif

#ifdef CONSTRUCTOR_F1
#include "../../PlatformDependent/Constructor/Include/Interface_Constructor.h"
#endif


#ifdef CONSTRUCTOR_L1
#include "../../PlatformDependent/Constructor/Include/Interface_Constructor.h"
#endif

HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *phadc);
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef *pHadc, uint32_t Timeout);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *pHadc);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

#endif