#include "Interface.h"
//#include gpio.h
//#include adc.h

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
                    // read adc
                    // turn rgb led on
                    // turn phet on
                    // hal_delay
                    // turn relay on
                    // hal_delay
                    // turn phet off
                    break;

                case FX_ON:
                    // turn all rgb led off
                    // turn phet on
                    // hal_delay
                    // turn relay off
                    // hal_delay
                    // turn phet off
                    break;
            }
        }
    
        case CHANNEL_B:
        {
            uint8_t temp = (stateB == FX_OFF) ? FX_ON : FX_OFF;
            stateB = temp;

            switch (stateB)
            {
            case FX_OFF:
                // read adc
                // turn rgb led on
                // turn phet on
                // hal_delay
                // turn relay on
                // hal_delay
                // turn phet off
                break;

            case FX_ON:
                // turn all rgb led off
                // turn phet on
                // hal_delay
                // turn relay off
                // hal_delay
                // turn phet off
                break;
            }
        }
    }

    return OK;
}

Status Interface_ToggleChannel(char channel)
{
    switch (channel) 
    {
        case CHANNEL_A:
            // read adc
            // toggle 1
            // delay 1
            // toggle 2
            // delay 2
            // toggle 3
            // delay 3
            break;
        case CHANNEL_B:
            // read adc
            // toggle 1
            // delay 1
            // toggle 2
            // delay 2
            // toggle 3
            // delay 3
            break;
    }
    return OK;
}