#ifndef __STM32F1xx_HAL_H
#define __STM32F1xx_HAL_H

typedef enum
{
  GPIO_PIN_RESET,
  GPIO_PIN_SET
} GPIO_PinState;

void HAL_GPIO_WritePin(void *pGPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(void *pGPIOx, uint16_t GPIO_Pin);
GPIO_PinState HAL_GPIO_ReadPin(void *GPIOx, uint16_t GPIO_Pin);

#endif
