/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_gpio.h"

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
#define A_SW_3_EXTI_Pin GPIO_PIN_13
#define A_SW_3_EXTI_GPIO_Port GPIOC
#define A_SW_3_EXTI_EXTI_IRQn EXTI15_10_IRQn
#define A_PROG_0_CTRL_Pin GPIO_PIN_14
#define A_PROG_0_CTRL_GPIO_Port GPIOC
#define A_PROG_1_CTRL_Pin GPIO_PIN_15
#define A_PROG_1_CTRL_GPIO_Port GPIOC
#define A_PROG_2_CTRL_Pin GPIO_PIN_0
#define A_PROG_2_CTRL_GPIO_Port GPIOA
#define MCU_SPI_CS_A_POT_Pin GPIO_PIN_1
#define MCU_SPI_CS_A_POT_GPIO_Port GPIOA
#define I2C_SELECT_1_Pin GPIO_PIN_2
#define I2C_SELECT_1_GPIO_Port GPIOA
#define I2C_SELECT_0_Pin GPIO_PIN_3
#define I2C_SELECT_0_GPIO_Port GPIOA
#define A_BTN_Pin GPIO_PIN_4
#define A_BTN_GPIO_Port GPIOA
#define A_BTN_EXTI_IRQn EXTI4_IRQn
#define MCU_TAP_EXTI_Pin GPIO_PIN_5
#define MCU_TAP_EXTI_GPIO_Port GPIOA
#define MCU_TAP_EXTI_EXTI_IRQn EXTI9_5_IRQn
#define B_ADC_POT_Pin GPIO_PIN_6
#define B_ADC_POT_GPIO_Port GPIOA
#define A_ADC_POT_Pin GPIO_PIN_7
#define A_ADC_POT_GPIO_Port GPIOA
#define A_LED_RED_Pin GPIO_PIN_0
#define A_LED_RED_GPIO_Port GPIOB
#define B_BTN_Pin GPIO_PIN_12
#define B_BTN_GPIO_Port GPIOB
#define B_BTN_EXTI_IRQn EXTI15_10_IRQn
#define B_LED_GREEN_Pin GPIO_PIN_13
#define B_LED_GREEN_GPIO_Port GPIOB
#define B_SW_1_EXTI_Pin GPIO_PIN_14
#define B_SW_1_EXTI_GPIO_Port GPIOB
#define B_SW_1_EXTI_EXTI_IRQn EXTI15_10_IRQn
#define B_SW_3_EXTI_Pin GPIO_PIN_15
#define B_SW_3_EXTI_GPIO_Port GPIOB
#define B_SW_3_EXTI_EXTI_IRQn EXTI15_10_IRQn
#define PHET_CTRL_Pin GPIO_PIN_8
#define PHET_CTRL_GPIO_Port GPIOA
#define B_PROG_2_CTRL_Pin GPIO_PIN_9
#define B_PROG_2_CTRL_GPIO_Port GPIOA
#define B_PROG_1_CTRL_Pin GPIO_PIN_10
#define B_PROG_1_CTRL_GPIO_Port GPIOA
#define B_PROG_2_CTRLA12_Pin GPIO_PIN_12
#define B_PROG_2_CTRLA12_GPIO_Port GPIOA
#define MCU_SPI_CS_B_POT_Pin GPIO_PIN_15
#define MCU_SPI_CS_B_POT_GPIO_Port GPIOA
#define MCU_SPI_CS_FLASH_Pin GPIO_PIN_6
#define MCU_SPI_CS_FLASH_GPIO_Port GPIOB
#define B_RELE_CTRL_Pin GPIO_PIN_7
#define B_RELE_CTRL_GPIO_Port GPIOB
#define A_RELE_CTRL_Pin GPIO_PIN_8
#define A_RELE_CTRL_GPIO_Port GPIOB
#define A_SW_1_EXTI_Pin GPIO_PIN_9
#define A_SW_1_EXTI_GPIO_Port GPIOB
#define A_SW_1_EXTI_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
