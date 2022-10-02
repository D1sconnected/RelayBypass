#include "../Include/Interface_Mimic.h"

volatile uint8_t  gFxStateA = FX_OFF;     // ToDo: load from memory
volatile uint8_t  gFxStateB = FX_OFF;     // ToDo: load from memory

volatile uint8_t  gProgramA = 0;
volatile uint8_t  gProgramB = 0;
volatile uint16_t gTimeA[FV1_MAX_PROGS] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000}; //ToDo: temp values, would be reloaded from SPI
volatile uint16_t gTimeB[FV1_MAX_PROGS] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};

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
            HAL_GPIO_WritePin(A_LED_RED_GPIO_Port, A_LED_RED_Pin, state);

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
            HAL_GPIO_WritePin(B_LED_GREEN_GPIO_Port, B_LED_GREEN_Pin, state);

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

    GPIO_PinState state = GPIO_PIN_SET;

    for (uint8_t i = 0; i <= 3; i++)
    {
        Interface_UpdateGpioForSwitch(channel, state);
        state = !state;
        HAL_Delay(200);
    }

    return OK;
}

Status Interface_ToggleForConfigMode(void)
{
    for (uint8_t i = 0; i <= 3; i++)
    {
        HAL_GPIO_TogglePin(A_LED_RED_GPIO_Port, A_LED_RED_Pin);
        HAL_GPIO_TogglePin(A_RELE_CTRL_GPIO_Port, A_RELE_CTRL_Pin);
        HAL_GPIO_TogglePin(B_LED_GREEN_GPIO_Port, B_LED_GREEN_Pin);
        HAL_GPIO_TogglePin(B_RELE_CTRL_GPIO_Port, B_RELE_CTRL_Pin);
        HAL_Delay(200);
    }

    // Turn Channel A 'ON'
    Interface_UpdateGpioForSwitch(CHANNEL_A, GPIO_PIN_SET);
    // Turn Channel B 'ON'
    Interface_UpdateGpioForSwitch(CHANNEL_B, GPIO_PIN_SET);

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

Status Interface_SwitchProgram(char channel, char specificator) 
{
    switch (channel)
    {
        case CHANNEL_A:
        {
            switch (specificator)
            {
                case UP:
                {
                    gProgramA++;

                    if (gProgramA > FV1_MAX_PROGS - 1)
                    {
                        gProgramA = 0;
                    }
                }
                break;

                case DOWN:
                {
                    gProgramA--;

                    if (!gProgramA)
                    {
                        gProgramA = FV1_MAX_PROGS - 1;
                    }
                }
                break;
            }

            HAL_GPIO_WritePin(A_PROG_0_CTRL_GPIO_Port, A_PROG_0_CTRL_Pin, (GPIO_PinState)(gProgramA & 0x01));
            HAL_GPIO_WritePin(A_PROG_1_CTRL_GPIO_Port, A_PROG_1_CTRL_Pin, (GPIO_PinState)((gProgramA & 0x02) >> 1));
            HAL_GPIO_WritePin(A_PROG_2_CTRL_GPIO_Port, A_PROG_2_CTRL_Pin, (GPIO_PinState)((gProgramA & 0x04) >> 2));

            // ToDo: Read saved TAP_MAX from SPI Flash and store to gCurrentMaxTap
        }
        break;

        case CHANNEL_B:
        {
            switch (specificator)
            {
            case UP:
            {
                gProgramB++;

                if (gProgramB > FV1_MAX_PROGS - 1)
                {
                    gProgramB = 0;
                }
            }
            break;

            case DOWN:
            {
                gProgramB--;

                if (!gProgramB)
                {
                    gProgramB = FV1_MAX_PROGS - 1;
                }
            }
            break;
            }

            HAL_GPIO_WritePin(B_PROG_0_CTRL_GPIO_Port, B_PROG_0_CTRL_Pin, (GPIO_PinState)(gProgramB & 0x01));
            HAL_GPIO_WritePin(B_PROG_1_CTRL_GPIO_Port, B_PROG_1_CTRL_Pin, (GPIO_PinState)((gProgramB & 0x02) >> 1));
            HAL_GPIO_WritePin(B_PROG_2_CTRL_GPIO_Port, B_PROG_2_CTRL_Pin, (GPIO_PinState)((gProgramB & 0x04) >> 2));

            // ToDo: Read saved TAP_MAX from SPI Flash and store to gCurrentMaxTap
        }
        break;
     }

    return OK;
}

Status Interface_SwitchEeprom(char channel)
{
    switch (channel)
    {
        case CHANNEL_A:
        {
            HAL_GPIO_WritePin(I2C_SELECT_0_GPIO_Port, I2C_SELECT_0_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(I2C_SELECT_1_GPIO_Port, I2C_SELECT_1_Pin, GPIO_PIN_SET);
        }
        break;

        case CHANNEL_B:
        {
            HAL_GPIO_WritePin(I2C_SELECT_0_GPIO_Port, I2C_SELECT_0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(I2C_SELECT_1_GPIO_Port, I2C_SELECT_1_Pin, GPIO_PIN_RESET);
        }
        break;
    }

    return OK;
}

// ToDo: value is inverting before send due inverted connection on board
Status Interface_UpdateDigitalPot(char channel, uint8_t value)
{
    uint8_t invertedValue = ~value;
    uint8_t cmd = MCP41010_CMD_WRITE;

    HAL_StatusTypeDef status = -1;

    switch (channel) 
    {
        case CHANNEL_A: 
        {
            HAL_GPIO_WritePin(MCU_SPI_CS_A_POT_GPIO_Port, MCU_SPI_CS_A_POT_Pin, GPIO_PIN_RESET);
            status =  HAL_SPI_Transmit(&hspi1, &cmd, sizeof(cmd), 5000);
            status += HAL_SPI_Transmit(&hspi1, &invertedValue, sizeof(invertedValue), 5000);
            HAL_GPIO_WritePin(MCU_SPI_CS_A_POT_GPIO_Port, MCU_SPI_CS_A_POT_Pin, GPIO_PIN_SET);
        }
        break;

        case CHANNEL_B:
        {
            HAL_GPIO_WritePin(MCU_SPI_CS_B_POT_GPIO_Port, MCU_SPI_CS_B_POT_Pin, GPIO_PIN_RESET);
            status =  HAL_SPI_Transmit(&hspi1, &cmd, sizeof(cmd), 5000);
            status += HAL_SPI_Transmit(&hspi1, &invertedValue, sizeof(invertedValue), 5000);
            HAL_GPIO_WritePin(MCU_SPI_CS_B_POT_GPIO_Port, MCU_SPI_CS_B_POT_Pin, GPIO_PIN_SET);
        }
        break;
    }

    if (!status) 
    {
        return OK;
    }

    return FAIL;
}

Status Interface_UpdateTap(char channel, uint16_t number)
{
    // Get [maxTap] for selected [gProgram]
    uint16_t maxTap = 0;
    if (channel == CHANNEL_A)
    {
        maxTap = gTimeA[gProgramA];
    }
    else
    {
        maxTap = gTimeB[gProgramB];
    }

    // Suppress number to maxTap
    if (number > maxTap)
    {
        number = maxTap;
    }

    // Divide [maxTap] in ms by [digital pot resolution]
    float coef = (float)maxTap / (float)(MCP41010_RESOLUTION);
    float floatNumber = (float)number;
    uint8_t value = (uint8_t)(floatNumber / coef);

    // Finally, update digital pot with calculated step from 0..MCP41010_RESOLUTION i.e. [value]
    Status status = Interface_UpdateDigitalPot(channel, value);

    return status;
}

Status Interface_UpdateMaxTimeForTap(char channel, char specificator)
{
    if (specificator == WRITE) 
    {
        //ToDo: Write locals timeA & timeB to to SPI memory
    }

    uint8_t prog = 0;
    switch (channel)
    {
        case CHANNEL_A:
        {
            prog += (HAL_GPIO_ReadPin(A_PROG_0_CTRL_GPIO_Port, A_PROG_0_CTRL_Pin));
            prog += (HAL_GPIO_ReadPin(A_PROG_1_CTRL_GPIO_Port, A_PROG_1_CTRL_Pin) << 1);
            prog += (HAL_GPIO_ReadPin(A_PROG_2_CTRL_GPIO_Port, A_PROG_2_CTRL_Pin) << 2);

            switch (specificator)
            {
                case UP:
                {
                    if (gTimeA[prog] != FV1_MAX_TIME)
                    {
                        gTimeA[prog] += FV1_TAP_STEP;
                    }
                }
                break;

                case DOWN:
                {
                    if (gTimeA[prog] != FV1_MIN_TIME)
                    {
                        gTimeA[prog] -= FV1_TAP_STEP;
                    }
                }
                break;
            }
        }
        break;

        case CHANNEL_B:
        {
            prog += (HAL_GPIO_ReadPin(B_PROG_0_CTRL_GPIO_Port, B_PROG_0_CTRL_Pin));
            prog += (HAL_GPIO_ReadPin(B_PROG_1_CTRL_GPIO_Port, B_PROG_1_CTRL_Pin) << 1);
            prog += (HAL_GPIO_ReadPin(B_PROG_2_CTRL_GPIO_Port, B_PROG_2_CTRL_Pin) << 2);

            switch (specificator)
            {
                case UP:
                {
                    if (gTimeB[prog] != FV1_MAX_TIME)
                    {
                        gTimeB[prog] += FV1_TAP_STEP;
                    }
                }
                break;

                case DOWN:
                {
                    if (gTimeB[prog] != FV1_MIN_TIME)
                    {
                        gTimeB[prog] -= FV1_TAP_STEP;
                    }
                }
                break;
            }
        }
        break;
    }

    return OK;
}
