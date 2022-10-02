/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "../../../../SharedLibs/RelayBypass/Include/List.h"
#include "../../../../SharedLibs/RelayBypass/Include/Common.h"
#include "../../../../SharedLibs/RelayBypass/Include/Timer.h"
/* USER CODE END Includes */

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

/* USER CODE BEGIN Private defines */
extern volatile bool      gTappedOnce;    // flag to detect first tap
extern volatile bool      gTapConfigMode; // flag to detect entering in config mode
extern volatile uint16_t  gTapLedA;       // tapStamp to represent led indicaton on channel A
extern volatile uint16_t  gTapLedB;       // tapStamp to represent led indicaton on channel B
extern volatile uint16_t  gTapStampA;     // tapStamp to represent tap value on channel A
extern volatile uint16_t  gTapStampB;     // tapStamp to represent tap value on channel B
extern volatile uint16_t *gTapPointer;    // pointer to work with gTapStampA or gTapStampB
/* USER CODE END Private defines */

void MX_TIM2_Init(void);
void MX_TIM3_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
