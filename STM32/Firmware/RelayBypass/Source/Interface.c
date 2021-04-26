#include "../Include/Interface.h"
//#include gpio.h

Status Interface_SwitchChannel(char channel) 
{
    static uint8_t stateA = FX_OFF;
    static uint8_t stateB = FX_OFF;
    
    if ((channel != CHANNEL_A) && (channel != CHANNEL_B)) 
    {
        return INVALID_FORMAT;
    }

    switch (channel) 
    {
        case CHANNEL_A:
        {
            uint8_t temp = (stateA == FX_OFF) ? FX_ON : FX_OFF;
            stateA = temp;

            switch (stateA)
            {
                case FX_OFF:
                {
                    // read adc
                    // turn rgb led on
                    // turn phet on
                    // hal_delay
                    // turn relay on
                    // hal_delay
                    // turn phet off
                }
                break;

                case FX_ON:
                {
                    // turn all rgb led off
                    // turn phet on
                    // hal_delay
                    // turn relay off
                    // hal_delay
                    // turn phet off
                }
                break;
            }
        }
        break;
    
        case CHANNEL_B:
        {
            uint8_t temp = (stateB == FX_OFF) ? FX_ON : FX_OFF;
            stateB = temp;

            switch (stateB)
            {
                case FX_OFF:
                {
                    // read adc
                    // turn rgb led on
                    // turn phet on
                    // hal_delay
                    // turn relay on
                    // hal_delay
                    // turn phet off
                }
                break;

                case FX_ON:
                {
                    // turn all rgb led off
                    // turn phet on
                    // hal_delay
                    // turn relay off
                    // hal_delay
                    // turn phet off
                }
                break;
            }
        }
        break;
    }
    return OK;
}

Status Interface_ToggleChannel(char channel)
{
    if ((channel != CHANNEL_A) && (channel != CHANNEL_B))
    {
        return INVALID_FORMAT;
    }

    switch (channel) 
    {
        case CHANNEL_A:
        {
            // Call HAL_ADC_GetValue and save result to adcResult
            // Identify LedColour based on adcResult
            // for cicle
            // Call HAL_GPIO_TogglePin to toggle specified LED
            // Call HAL_Delay to wait for LED to change state
        }
        break;

        case CHANNEL_B:
        {
            // Call HAL_ADC_GetValue and save result to adcResult
            // Identify LedColour based on adcResult
            // for cicle
            // Call HAL_GPIO_TogglePin to toggle specified LED
            // Call HAL_Delay to wait for LED to change state
        }
        break;
    }
    return OK;
}

Status Interface_ChangeRoute(char channel) 
{
    if ((channel != CHANNEL_A) && (channel != CHANNEL_B))
    {
        return INVALID_FORMAT;
    }

    switch (channel)
    {
        case CHANNEL_A:
        {
            // Call HAL_GPIO_WritePin to turn PHET ON
            // Call HAL_Delay to wait for PHET activation
            // Call HAL_GPIO_WritePin to turn OFF #1 DIRECTION_RELAY
            // Call HAL_GPIO_WritePin to turn OFF #2 DIRECTION_RELAY
            // Call HAL_Delay to suppress pop noise
            // Call HAL_GPIO_WritePin to turn PHET OFF
        }
        break;

        case CHANNEL_B:
        {
            // Call HAL_GPIO_WritePin to turn PHET ON
            // Call HAL_Delay to wait for PHET activation
            // Call HAL_GPIO_WritePin to turn ON #1 DIRECTION_RELAY
            // Call HAL_GPIO_WritePin to turn ON #2 DIRECTION_RELAY
            // Call HAL_Delay to suppress pop noise
            // Call HAL_GPIO_WritePin to turn PHET OFF
        }
        break;
    }
    return OK;
}

LedColour Interface_GetChannel(char channel)
{
    uint32_t adcResult = 0;

    switch (channel)
    {
    case CHANNEL_A:
        // read ADC with HAL_ADC_GetValue(adc1);
        adcResult = HAL_ADC_GetValue(&hadc1);
        break;
    case CHANNEL_B:
        // read ADC with HAL_ADC_GetValue(adc2);
        adcResult = HAL_ADC_GetValue(&hadc1);
        break;
    }

    if (ADC_MIN_GREEN_BOUND <= adcResult)
        return GREEN;
    else if (ADC_MIN_RED_BOUND <= adcResult < ADC_MIN_GREEN_BOUND)
        return RED;
    else if (ADC_MIN_BLUE_BOUND <= adcResult < ADC_MIN_RED_BOUND)
        return BLUE;
}