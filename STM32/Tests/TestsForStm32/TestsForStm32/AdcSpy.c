#include "AdcSpy.h"

ADC_HandleTypeDef hadc1;

uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *pHadc)
{
    switch (pHadc->colour)
    {
        case RED:
            return ADC_SPY_RED_VALUE;
            break;
        case GREEN:
            return ADC_SPY_GREEN_VALUE;
            break;
        case BLUE:
            return ADC_SPY_BLUE_VALUE;
            break;
    }
}

HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *phadc) 
{
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef *pHadc, uint32_t Timeout) 
{
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *pHadc) 
{
    return HAL_OK;
}

void ADC_Select_CH2(void) 
{
    return;
}
void ADC_Select_CH8(void) 
{
    return;
}




