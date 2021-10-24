#ifndef GPIOSPY_HEADER_FILE_H
#define GPIOSPY_HEADER_FILE_H

#ifdef STM32F1_VERSION
#include "../../../Firmware/MicroSdBootloader_STM32F101C4/Core/Inc/gpio.h"
#endif

#ifdef STM32L1_VERSION
#include "../../../Firmware/MicroSdBootloader_STM32L151C8/Core/Inc/gpio.h"
#endif

typedef struct 
{
    GPIO_PinState ledRedA;
    GPIO_PinState ledRedB;
    GPIO_PinState mcuProg;
} EmulatedGpioStatesStruct;

extern EmulatedGpioStatesStruct emulatedGpio;

void HAL_GPIO_WritePin(uint8_t GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(uint8_t GPIOx, uint16_t GPIO_Pin);

#endif
