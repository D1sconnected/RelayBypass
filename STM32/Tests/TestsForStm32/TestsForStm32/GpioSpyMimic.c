#include "GpioSpy.h"
#include "GpioSpyMimic.h"

static Node *pGpioList = NULL;

void HAL_GPIO_EXTI_Callback_Mimic(uint16_t GPIO_Pin)
{
    HAL_TIM_Base_Start_IT(&htim2);
    if ((GPIO_Pin & (A_BTN_Pin | B_BTN_Pin)) && ((gBtnStateA == false) || (gBtnStateB == false)))
    {

        if (GPIO_Pin & A_BTN_Pin)
        {
            gBtnStateA = true;
        }

        if (GPIO_Pin & B_BTN_Pin)
        {
            gBtnStateB = true;
        }
    }
}

GPIO_PinState HAL_GPIO_ReadPin_Mimic(uint8_t GPIOx, uint16_t GPIO_Pin)
{
    if (GPIOx == A_BTN_GPIO_Port && GPIO_Pin == A_BTN_Pin)
    {
        return emulatedGpio.buttonA;
    }

    else if (GPIOx == B_BTN_GPIO_Port && GPIO_Pin == B_BTN_Pin)
    {
        return emulatedGpio.buttonB;
    }
}

void HAL_GPIO_WritePin_Mimic(uint8_t GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) 
{
    switch (GPIOx) 
    {
        case GPIOA: 
        {
            switch (GPIO_Pin) 
            {
                case A_RELE_CTRL_Pin: 
                {
                    emulatedGpio.releA = PinState;
                }
                break;

                case A_LED_RED_Pin:
                {
                    emulatedGpio.ledRedA = PinState;
                }
                break;
            }
        }
        break;

        case GPIOB:
        {
            switch (GPIO_Pin)
            {
                case PHET_CTRL_Pin:
                {
                    emulatedGpio.phet = PinState;
                }
                break;

                case B_LED_GREEN_Pin:
                {
                    emulatedGpio.ledGreenB = PinState;
                }
                break;
            }
        }
        break;

        case GPIOC:
        {
            switch (GPIO_Pin)
            {
                case B_RELE_CTRL_Pin:
                {
                    emulatedGpio.releB = PinState;
                }
                break;
            }
        }
        break;
    }
}

void HAL_GPIO_TogglePin_Mimic(uint8_t GPIOx, uint16_t GPIO_Pin)
{
    switch (GPIOx)
    {
        case GPIOA:
        {
            switch (GPIO_Pin)
            {
                case A_RELE_CTRL_Pin:
                {
                    emulatedGpio.releA = !emulatedGpio.releA;
                }
                break;

                case A_LED_RED_Pin:
                {
                    emulatedGpio.ledRedA = !emulatedGpio.ledRedA;
                }
                break;
            }
        }
        break;

        case GPIOB:
        {
            switch (GPIO_Pin)
            {
                case PHET_CTRL_Pin:
                {
                    emulatedGpio.phet = !emulatedGpio.phet;
                }
                break;

                case B_LED_GREEN_Pin:
                {
                    emulatedGpio.ledGreenB = !emulatedGpio.ledGreenB;
                }
                break;
            }
        }
        break;
        case GPIOC:
        {
            switch (GPIO_Pin)
            {
                case B_RELE_CTRL_Pin:
                {
                    emulatedGpio.releB = !emulatedGpio.releB;
                }
                break;
            }
        }
        break;
    }
}