// InterfaceSpy.c
#include "InterfaceSpy.h"

LedColour Interface_GetChannel(char channel)
{
    uint32_t adcResult = 0;

    switch (channel)
    {
    case CHANNEL_A:
        // read ADC with HAL_ADC_GetValue(adc1);
        adcResult = InterfaceSpy_SetAdcValue(RED);
        break;
    case CHANNEL_B:
        // read ADC with HAL_ADC_GetValue(adc2);
        adcResult = InterfaceSpy_SetAdcValue(BLUE);
        break;
    }

    if (ADC_MIN_GREEN_BOUND <= adcResult)
        return GREEN;
    else if (ADC_MIN_RED_BOUND <= adcResult < ADC_MIN_GREEN_BOUND)
        return RED;
    else if (ADC_MIN_BLUE_BOUND <= adcResult < ADC_MIN_RED_BOUND)
        return BLUE;
}

uint32_t InterfaceSpy_SetAdcValue(LedColour colour)
{
    switch (colour)
    {
        case RED:
            return INTERFACE_SPY_RED_VALUE;
            break;
        case GREEN:
            return INTERFACE_SPY_GREEN_VALUE;
            break;
        case BLUE:
            return INTERFACE_SPY_BLUE_VALUE;
            break;
    }
}