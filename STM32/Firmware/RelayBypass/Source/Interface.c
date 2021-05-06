#include "../Include/Interface.h"

void Interface_UpdateGpioForToggle(char channel, LedColour colour)
{
    switch (channel)
    {
        case CHANNEL_A:
        {
            // Update LED state
            if (colour == RED)
            {
                HAL_GPIO_TogglePin(A_LED_RED_GPIO_Port, A_LED_RED_Pin);
            }

            else if (colour == GREEN)
            {
                HAL_GPIO_TogglePin(A_LED_GREEN_GPIO_Port, A_LED_GREEN_Pin);
            }

            else if (colour == BLUE)
            {
                HAL_GPIO_TogglePin(A_LED_BLUE_GPIO_Port, A_LED_BLUE_Pin);
            }
        }
        break;

        case CHANNEL_B:
        {
            // Update LED state
            if (colour == RED)
            {
                HAL_GPIO_TogglePin(B_LED_RED_GPIO_Port, B_LED_RED_Pin);
            }

            else if (colour == GREEN)
            {
                HAL_GPIO_TogglePin(B_LED_GREEN_GPIO_Port, B_LED_GREEN_Pin);
            }

            else if (colour == BLUE)
            {
                HAL_GPIO_TogglePin(B_LED_BLUE_GPIO_Port, B_LED_BLUE_Pin);
            }
        }
        break;
    }
}

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

    LedColour colour = NONE;

    switch (channel) 
    {
        case CHANNEL_A:
        {
            uint8_t temp = (stateA == FX_OFF) ? FX_ON : FX_OFF;
            stateA = temp;

            switch (stateA)
            {
                case FX_ON:
                {
                    colour = Interface_GetColour(channel);
                    Interface_UpdateGpioForSwitch(channel, colour, GPIO_PIN_SET);
                }
                break;

                case FX_OFF:
                {
                    colour = Interface_GetColour(channel);
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
                case FX_ON:
                {
                    colour = Interface_GetColour(channel);
                    Interface_UpdateGpioForSwitch(channel, colour, GPIO_PIN_SET);
                }
                break;

                case FX_OFF:
                {
                    colour = Interface_GetColour(channel);
                    Interface_UpdateGpioForSwitch(channel, colour, GPIO_PIN_RESET);
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

    LedColour colour = Interface_GetColour(channel);

    for (uint8_t i = 0; i <= 3; i++)
    {
        Interface_UpdateGpioForToggle(channel, colour);
        HAL_Delay(300);
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

LedColour Interface_GetColour(char channel)
{
    GPIO_PinState code0 = GPIO_PIN_RESET;
    GPIO_PinState code1 = GPIO_PIN_RESET;

    switch (channel)
    {
    case CHANNEL_A:
        // Read A_CODE_0 & A_CODE_1
        code0 = HAL_GPIO_ReadPin(A_CODE_0_GPIO_Port, A_CODE_0_Pin);
        code1 = HAL_GPIO_ReadPin(A_CODE_1_GPIO_Port, A_CODE_1_Pin);
        break;
    case CHANNEL_B:
        // Read B_CODE_0 & B_CODE_1
        code0 = HAL_GPIO_ReadPin(B_CODE_0_GPIO_Port, B_CODE_0_Pin);
        code1 = HAL_GPIO_ReadPin(B_CODE_1_GPIO_Port, B_CODE_1_Pin);
        break;
    }

    if (code0 == GPIO_PIN_SET && code1 == GPIO_PIN_SET)
    {
        return GREEN;
    }
    else if (code0 == GPIO_PIN_RESET && code1 == GPIO_PIN_SET)
    {
        return RED;
    }
    else if (code0 == GPIO_PIN_SET && code1 == GPIO_PIN_RESET)
    {
        return BLUE;
    }

    return NONE;
}
