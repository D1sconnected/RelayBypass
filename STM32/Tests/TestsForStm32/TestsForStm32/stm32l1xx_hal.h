#ifndef __STM32L1xx_HAL_H
#define __STM32L1xx_HAL_H

#include "../../../SharedLibs/RelayBypass/Include/Common.h"
#include <stdint.h>

#define GPIO_PIN_0     ((uint16_t)0x0001)
#define GPIO_PIN_1     ((uint16_t)0x0002)
#define GPIO_PIN_2     ((uint16_t)0x0004)
#define GPIO_PIN_3     ((uint16_t)0x0008)
#define GPIO_PIN_4     ((uint16_t)0x0010)
#define GPIO_PIN_5     ((uint16_t)0x0020)
#define GPIO_PIN_6     ((uint16_t)0x0040)
#define GPIO_PIN_7     ((uint16_t)0x0080)
#define GPIO_PIN_8     ((uint16_t)0x0100)
#define GPIO_PIN_9     ((uint16_t)0x0200)
#define GPIO_PIN_10    ((uint16_t)0x0400)
#define GPIO_PIN_11    ((uint16_t)0x0800)
#define GPIO_PIN_12    ((uint16_t)0x1000)
#define GPIO_PIN_13    ((uint16_t)0x2000)
#define GPIO_PIN_14    ((uint16_t)0x4000)
#define GPIO_PIN_15    ((uint16_t)0x8000)

#define GPIOA   0x0A
#define GPIOB   0x0B
#define GPIOC   0x0C

#define EXTI3_IRQn
#define EXTI15_10_IRQn

typedef enum
{
  GPIO_PIN_RESET,
  GPIO_PIN_SET
} GPIO_PinState;

typedef enum
{
    HAL_OK,
    HAL_ERROR,
    HAL_BUSY,
    HAL_TIMEOUT
} HAL_StatusTypeDef;

typedef struct ADC_HandleTypeDef
{
    uint8_t colour;
} ADC_HandleTypeDef;

typedef struct TIM_HandleTypeDef
{
    uint8_t timeMs;
} TIM_HandleTypeDef;

// ToDo: Place to different files
void HAL_Delay(uint32_t Delay);

extern GPIO_PinState HAL_GPIO_ReadPin(uint8_t GPIOx, uint16_t GPIO_Pin);
extern void HAL_GPIO_WritePin(uint8_t GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
extern void HAL_GPIO_TogglePin(uint8_t GPIOx, uint16_t GPIO_Pin);
extern void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

extern HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *pHtim);
extern HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *pHtim);
extern void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif
