// GpioSpy.h
#ifndef GPIOSPY_HEADER_FILE_H
#define GPIOSPY_HEADER_FILE_H

#include "gpio.h"

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
