#include "AdcSpy.h"

ADC_HandleTypeDef hadc1;

uint16_t adcData[2] = {0};

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

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    static uint16_t adcPotA = 0;
    static uint16_t adcPotB = 0;

    StateStruct cmdBlock = {0};

    if (adcData[1] / 16 != adcPotA) 
    {
        adcPotA = adcData[1] / 16;
        cmdBlock.state = EXECUTOR_STATE_UPDATE_DIGITAL_POT_BY_ADC;
        cmdBlock.channel = CHANNEL_A;
        cmdBlock.number = adcPotA;
        Button_PushCommand(&cmdBlock); // ToDo: rename 
    }

    if (adcData[0] / 16 != adcPotB)
    {
        adcPotB = adcData[0] / 16;
        cmdBlock.state = EXECUTOR_STATE_UPDATE_DIGITAL_POT_BY_ADC;
        cmdBlock.channel = CHANNEL_B;
        cmdBlock.number = adcPotB;
        Button_PushCommand(&cmdBlock);  // ToDo: rename 
    }

    return;
}