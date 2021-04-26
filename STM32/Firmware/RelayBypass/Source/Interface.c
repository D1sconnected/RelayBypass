#include "../Include/Interface.h"

void Interface_UpdateGpioForSwitch(char channel, LedColour colour, GPIO_PinState state)
{
    switch (channel)
    {
        case CHANNEL_A:
        {
            // Update LED state
            if (colour == RED) 
            {
                HAL_GPIO_WritePin(A_LED_RED_GPIO_Port, A_LED_RED_Pin, state);
            }

            else if (colour == GREEN) 
            {
                HAL_GPIO_WritePin(A_LED_GREEN_GPIO_Port, A_LED_GREEN_Pin, state);
            }

            else if (colour == BLUE)
            {
                HAL_GPIO_WritePin(A_LED_BLUE_GPIO_Port, A_LED_BLUE_Pin, state);
            }

            // Turn PHET ON
            HAL_GPIO_WritePin(PHET_GPIO_Port, PHET_Pin, GPIO_PIN_SET);

            // Wait for PHET to turn ON
            HAL_Delay(BYPASS_DELAY);

            // Update RELAY state
            HAL_GPIO_WritePin(A_RELE_GPIO_Port, A_RELE_Pin, state);

            // Wait for RELAY to switch state
            HAL_Delay(BYPASS_DELAY);

            // Turn PHET OFF
            HAL_GPIO_WritePin(PHET_GPIO_Port, PHET_Pin, GPIO_PIN_RESET);
        }
        break;

        case CHANNEL_B:
        {
            // Update LED state
            if (colour == RED)
            {
                HAL_GPIO_WritePin(B_LED_RED_GPIO_Port, B_LED_RED_Pin, state);
            }

            else if (colour == GREEN)
            {
                HAL_GPIO_WritePin(B_LED_GREEN_GPIO_Port, B_LED_GREEN_Pin, state);
            }

            else if (colour == BLUE)
            {
                HAL_GPIO_WritePin(B_LED_BLUE_GPIO_Port, B_LED_BLUE_Pin, state);
            }

            // Turn PHET ON
            HAL_GPIO_WritePin(PHET_GPIO_Port, PHET_Pin, GPIO_PIN_SET);

            // Wait for PHET to turn ON
            HAL_Delay(BYPASS_DELAY);

            // Update RELAY state
            HAL_GPIO_WritePin(B_RELE_GPIO_Port, B_RELE_Pin, state);

            // Wait for RELAY to switch state
            HAL_Delay(BYPASS_DELAY);

            // Turn PHET OFF
            HAL_GPIO_WritePin(PHET_GPIO_Port, PHET_Pin, GPIO_PIN_RESET);
        }
        break;
    }
}

void Interface_UpdateGpioForChange(GPIO_PinState state)
{
    // Turn PHET ON
    HAL_GPIO_WritePin(PHET_GPIO_Port, PHET_Pin, GPIO_PIN_SET);

    // Wait for PHET to turn ON
    HAL_Delay(BYPASS_DELAY);

    // Update DIR 0 RELAY state
    HAL_GPIO_WritePin(DIR0_RELE_GPIO_Port, DIR0_RELE_Pin, state);

    // Update DIR 1 RELAY state
    HAL_GPIO_WritePin(DIR1_RELE_GPIO_Port, DIR1_RELE_Pin, state);

    // Wait for RELAYs to switch state
    HAL_Delay(BYPASS_DELAY);

    // Turn PHET OFF
    HAL_GPIO_WritePin(PHET_GPIO_Port, PHET_Pin, GPIO_PIN_RESET);
}

Status Interface_SwitchChannel(char channel) 
{
    static uint8_t stateA = FX_OFF;
    static uint8_t stateB = FX_OFF;
    
    if ((channel != CHANNEL_A) && (channel != CHANNEL_B)) 
    {
        return INVALID_FORMAT;
    }

    LedColour colour = -1;
    Status status = OK;

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
                    status = Interface_GetColour(channel, &colour);
                    Interface_UpdateGpioForSwitch(channel, colour, GPIO_PIN_SET);
                }
                break;

                case FX_ON:
                {
                    status = Interface_GetColour(channel, &colour);
                    Interface_UpdateGpioForSwitch(channel, colour, GPIO_PIN_RESET);
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
                    status = Interface_GetColour(channel, &colour);
                    Interface_UpdateGpioForSwitch(channel, colour, GPIO_PIN_SET);
                }
                break;

                case FX_ON:
                {
                    status = Interface_GetColour(channel, &colour);
                    Interface_UpdateGpioForSwitch(channel, colour, GPIO_PIN_RESET);
                }
                break;
            }
        }
        break;
    }
    return status;
}

Status Interface_ToggleChannel(char channel)
{
    if ((channel != CHANNEL_A) && (channel != CHANNEL_B))
    {
        return INVALID_FORMAT;
    }

    LedColour colour = -1;
    Status status = OK;
    GPIO_PinState state = GPIO_PIN_RESET;

    status = Interface_GetColour(channel, &colour);

    if (status != OK) 
    {
        return status;
    }

    for (uint8_t i = 0; i <= 3; i++)
    {
        Interface_UpdateGpioForSwitch(channel, colour, state);
        state = !state;
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
            Interface_UpdateGpioForChange(GPIO_PIN_RESET);
        }
        break;

        case CHANNEL_B:
        {
            Interface_UpdateGpioForChange(GPIO_PIN_SET);
        }
        break;
    }
    return OK;
}

Status Interface_GetColour(char channel, LedColour *pColour)
{
    Status   status = OK;
    uint32_t adcResult = 0;

    switch (channel)
    {
    case CHANNEL_A:
        // read ADC on ADC1 CH2 (A_ADC)
        ADC_Select_CH2();
        status += HAL_ADC_Start(&hadc1);
        status += HAL_ADC_PollForConversion(&hadc1, 1000);
        adcResult = HAL_ADC_GetValue(&hadc1);
        status += HAL_ADC_Stop(&hadc1);
        break;
    case CHANNEL_B:
        // read ADC on ADC1 CH8 (B_ADC)
        ADC_Select_CH8();
        status += HAL_ADC_Start(&hadc1);
        status += HAL_ADC_PollForConversion(&hadc1, 1000);
        adcResult = HAL_ADC_GetValue(&hadc1);
        status += HAL_ADC_Stop(&hadc1);
        break;
    }

    if (ADC_MIN_GREEN_BOUND <= adcResult) 
    {
        *pColour = GREEN;
    }
    else if (ADC_MIN_RED_BOUND <= adcResult < ADC_MIN_GREEN_BOUND) 
    {
        *pColour = RED;
    }
    else if (ADC_MIN_BLUE_BOUND <= adcResult < ADC_MIN_RED_BOUND) 
    {
        *pColour = BLUE;
    }

    return status;
}