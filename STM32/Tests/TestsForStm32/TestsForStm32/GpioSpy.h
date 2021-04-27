// GpioSpy.h
#ifndef GPIOSPY_HEADER_FILE_H
#define GPIOSPY_HEADER_FILE_H

#include "gpio.h"

typedef struct 
{
    GPIO_PinState buttonA;
    GPIO_PinState buttonB;
} EmulatedGpioStatesStruct;

extern EmulatedGpioStatesStruct emulatedGpio;

GPIO_PinState HAL_GPIO_ReadPin(void* pGPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(void* pGPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(void* pGPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
