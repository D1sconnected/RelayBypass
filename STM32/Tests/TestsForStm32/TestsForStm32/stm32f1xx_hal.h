#ifndef __STM32F1xx_HAL_H
#define __STM32F1xx_HAL_H

#include "../../Include/Common.h"

typedef enum
{
  GPIO_PIN_RESET,
  GPIO_PIN_SET
} GPIO_PinState;

typedef struct ADC_HandleTypeDef
{
    uint8_t colour;
} ADC_HandleTypeDef;

// ToDo: Place to different files
void HAL_GPIO_WritePin(void *pGPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(void *pGPIOx, uint16_t GPIO_Pin);
void HAL_Delay(uint32_t Delay);

#endif
