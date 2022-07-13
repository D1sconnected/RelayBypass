#include "../Include/Interface_Mimic.h"

uint8_t gFxStateA = FX_OFF;
uint8_t gFxStateB = FX_OFF;

void Interface_UpdateGpioForToggle(char channel)
{
    switch (channel)
    {
        case CHANNEL_A:
        {
            HAL_GPIO_TogglePin(A_LED_RED_GPIO_Port, A_LED_RED_Pin);
        }
        break;

        case CHANNEL_B:
        {
            HAL_GPIO_TogglePin(B_LED_GREEN_GPIO_Port, B_LED_GREEN_Pin);
        }
        break;
    }
}

void Interface_UpdateGpioForSwitch(char channel, GPIO_PinState state)
{
    switch (channel)
    {
        case CHANNEL_A:
        {
            // Update LED state
            HAL_GPIO_TogglePin(A_LED_RED_GPIO_Port, A_LED_RED_Pin);

            // Turn PHET ON
            HAL_GPIO_WritePin(PHET_CTRL_GPIO_Port, PHET_CTRL_Pin, GPIO_PIN_SET);

            // Wait for PHET to turn ON
            HAL_Delay(BYPASS_DELAY);

            // Update RELAY state
            HAL_GPIO_WritePin(A_RELE_CTRL_GPIO_Port, A_RELE_CTRL_Pin, state);

            // Wait for RELAY to switch state
            HAL_Delay(BYPASS_DELAY);

            // Turn PHET OFF
            HAL_GPIO_WritePin(PHET_CTRL_GPIO_Port, PHET_CTRL_Pin, GPIO_PIN_RESET);
        }
        break;

        case CHANNEL_B:
        {
            // Update LED state
            HAL_GPIO_TogglePin(B_LED_GREEN_GPIO_Port, B_LED_GREEN_Pin);

            // Turn PHET ON
            HAL_GPIO_WritePin(PHET_CTRL_GPIO_Port, PHET_CTRL_Pin, GPIO_PIN_SET);

            // Wait for PHET to turn ON
            HAL_Delay(BYPASS_DELAY);

            // Update RELAY state
            HAL_GPIO_WritePin(B_RELE_CTRL_GPIO_Port, B_RELE_CTRL_Pin, state);

            // Wait for RELAY to switch state
            HAL_Delay(BYPASS_DELAY);

            // Turn PHET OFF
            HAL_GPIO_WritePin(PHET_CTRL_GPIO_Port, PHET_CTRL_Pin, GPIO_PIN_RESET);
        }
        break;
    }
}

void Interface_UpdateGpioForChange(GPIO_PinState state)
{
    return;
}

Status Interface_SwitchChannel(char channel)
{
    
    if ((channel != CHANNEL_A) && (channel != CHANNEL_B)) 
    {
        return INVALID_FORMAT;
    }

    switch (channel) 
    {
        case CHANNEL_A:
        {
            uint8_t temp = (gFxStateA == FX_OFF) ? FX_ON : FX_OFF;
            gFxStateA = temp;

            switch (gFxStateA)
            {
                case FX_ON:
                {
                    Interface_UpdateGpioForSwitch(channel, GPIO_PIN_SET);
                }
                break;

                case FX_OFF:
                {
                    Interface_UpdateGpioForSwitch(channel, GPIO_PIN_RESET);
                }
                break;
            }
        }
        break;
    
        case CHANNEL_B:
        {
            uint8_t temp = (gFxStateB == FX_OFF) ? FX_ON : FX_OFF;
            gFxStateB = temp;

            switch (gFxStateB)
            {
                case FX_ON:
                {
                    Interface_UpdateGpioForSwitch(channel, GPIO_PIN_SET);
                }
                break;

                case FX_OFF:
                {
                    Interface_UpdateGpioForSwitch(channel, GPIO_PIN_RESET);
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

    for (uint8_t i = 0; i <= 3; i++)
    {
        Interface_UpdateGpioForToggle(channel);
        HAL_Delay(300);
    }

    return OK;
}

Status Interface_ChangeRoute(char channel) 
{
    return OK;
}

LedColour Interface_GetColour(char channel)
{
    return NONE;
}
