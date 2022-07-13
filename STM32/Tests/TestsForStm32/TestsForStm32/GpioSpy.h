// GpioSpy.h
#ifndef GPIOSPY_HEADER_FILE_H
#define GPIOSPY_HEADER_FILE_H

#ifdef STM32F1_VERSION
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/tim.h"
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/gpio.h"
#endif

#ifdef STM32L1_VERSION
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/tim.h"
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/gpio.h"
#endif

#include "../../../SharedLibs/RelayBypass/Include/Button.h"

typedef struct 
{
    GPIO_PinState buttonA;
    GPIO_PinState buttonB;
    GPIO_PinState codeA0;
    GPIO_PinState codeA1;
    GPIO_PinState codeB0;
    GPIO_PinState codeB1;
    GPIO_PinState releA;
    GPIO_PinState releB;
    GPIO_PinState releDir0;
    GPIO_PinState releDir1;
    GPIO_PinState ledRedA;
    GPIO_PinState ledGreenA;
    GPIO_PinState ledBlueA;
    GPIO_PinState ledRedB;
    GPIO_PinState ledGreenB;
    GPIO_PinState ledBlueB;
    GPIO_PinState phet;
    GPIO_PinState mcuProg;
    GPIO_PinState prog0A;
    GPIO_PinState prog1A;
    GPIO_PinState prog2A;
    GPIO_PinState prog0B;
    GPIO_PinState prog1B;
    GPIO_PinState prog2B;
    GPIO_PinState switch1A;
    GPIO_PinState switch3A;
    GPIO_PinState switch1B;
    GPIO_PinState switch3B;

} EmulatedGpioStatesStruct;

extern EmulatedGpioStatesStruct emulatedGpio;

GPIO_PinState HAL_GPIO_ReadPin(uint8_t GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(uint8_t GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(uint8_t GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
