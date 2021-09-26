/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_system.h"
#include "stm32l1xx_ll_exti.h"
#include "stm32l1xx_ll_cortex.h"
#include "stm32l1xx_ll_utils.h"
#include "stm32l1xx_ll_pwr.h"
#include "stm32l1xx_ll_dma.h"
#include "stm32l1xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B_RELE_Pin GPIO_PIN_13
#define B_RELE_GPIO_Port GPIOC
#define DIR0_RELE_Pin GPIO_PIN_14
#define DIR0_RELE_GPIO_Port GPIOC
#define B_LED_BLUE_Pin GPIO_PIN_15
#define B_LED_BLUE_GPIO_Port GPIOC
#define B_CODE_1_Pin GPIO_PIN_1
#define B_CODE_1_GPIO_Port GPIOA
#define B_CODE_0_Pin GPIO_PIN_2
#define B_CODE_0_GPIO_Port GPIOA
#define B_BTN_Pin GPIO_PIN_3
#define B_BTN_GPIO_Port GPIOA
#define B_BTN_EXTI_IRQn EXTI3_IRQn
#define A_RELE_Pin GPIO_PIN_4
#define A_RELE_GPIO_Port GPIOA
#define A_CODE_0_Pin GPIO_PIN_0
#define A_CODE_0_GPIO_Port GPIOB
#define A_CODE_1_Pin GPIO_PIN_1
#define A_CODE_1_GPIO_Port GPIOB
#define MCU_PROG_Pin GPIO_PIN_2
#define MCU_PROG_GPIO_Port GPIOB
#define A_BTN_Pin GPIO_PIN_11
#define A_BTN_GPIO_Port GPIOB
#define A_BTN_EXTI_IRQn EXTI15_10_IRQn
#define PHET_Pin GPIO_PIN_12
#define PHET_GPIO_Port GPIOB
#define DIR1_RELE_Pin GPIO_PIN_13
#define DIR1_RELE_GPIO_Port GPIOB
#define A_LED_GREEN_Pin GPIO_PIN_14
#define A_LED_GREEN_GPIO_Port GPIOB
#define A_LED_BLUE_Pin GPIO_PIN_15
#define A_LED_BLUE_GPIO_Port GPIOB
#define A_LED_RED_Pin GPIO_PIN_8
#define A_LED_RED_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_15
#define SPI1_CS_GPIO_Port GPIOA
#define B_LED_GREEN_Pin GPIO_PIN_8
#define B_LED_GREEN_GPIO_Port GPIOB
#define B_LED_RED_Pin GPIO_PIN_9
#define B_LED_RED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
