#include "adcSpy.h"

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