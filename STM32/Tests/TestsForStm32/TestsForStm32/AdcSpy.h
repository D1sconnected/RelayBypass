// AdcSpy.h
#ifndef ADCSPY_HEADER_FILE_H
#define ADCSPY_HEADER_FILE_H

#define ADC_SPY_GREEN_VALUE 3800
#define ADC_SPY_RED_VALUE   2500
#define ADC_SPY_BLUE_VALUE  1300

//#include "adc.h"
#include "Common.h"
#include "Interface.h"

HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *phadc);
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef *pHadc, uint32_t Timeout);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *pHadc);

#endif