#include "GpioSpy.h"

#ifdef CONSTRUCTOR_F1
#include "GpioSpyConstructor.h"
#endif

#ifdef MIMIC_F1
#include "GpioSpyMimic.h"
#endif

static Node *pGpioList = NULL;

EmulatedGpioStatesStruct emulatedGpio = {0};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    #ifdef CONSTRUCTOR_F1
        HAL_GPIO_EXTI_Callback_Constructor(GPIO_Pin);
    #endif

    #ifdef MIMIC_F1
        HAL_GPIO_EXTI_Callback_Mimic(GPIO_Pin);
    #endif
}

GPIO_PinState HAL_GPIO_ReadPin(uint8_t GPIOx, uint16_t GPIO_Pin)
{
    #ifdef CONSTRUCTOR_F1
        HAL_GPIO_ReadPin_Constructor(GPIOx, GPIO_Pin);
    #endif

    #ifdef MIMIC_F1
        HAL_GPIO_ReadPin_Mimic(GPIOx, GPIO_Pin);
    #endif
}

void HAL_GPIO_WritePin(uint8_t GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) 
{
    #ifdef CONSTRUCTOR_F1
        HAL_GPIO_WritePin_Constructor(GPIOx, GPIO_Pin, PinState);
    #endif

    #ifdef MIMIC_F1
        HAL_GPIO_WritePin_Mimic(GPIOx, GPIO_Pin, PinState);
    #endif
}

void HAL_GPIO_TogglePin(uint8_t GPIOx, uint16_t GPIO_Pin)
{
    #ifdef CONSTRUCTOR_F1
        HAL_GPIO_TogglePin_Constructor(GPIOx, GPIO_Pin);
    #endif

    #ifdef MIMIC_F1
        HAL_GPIO_TogglePin_Mimic(GPIOx, GPIO_Pin);
    #endif
}

//ToDo: Place in different location
void HAL_Delay() 
{
	return;
}