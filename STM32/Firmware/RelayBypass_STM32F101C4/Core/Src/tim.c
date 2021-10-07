/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
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

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
//extern bool gBtnStateA;
//extern bool gBtnStateB;

//static Node* pLocalTimList = NULL;
/* USER CODE END 0 */

TIM_HandleTypeDef htim2;

/* TIM2 init function */
void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 32000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 125;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /* TIM2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    Timer_Callback(htim);
}

//Status USER_TIM_PushCommand(StateStruct* pCmd)
//{
//    if (pCmd == NULL)
//    {
//        return INVALID_PARAMETERS;
//    }
//
//    List_PushBack(&pLocalTimList, *pCmd);
//
//    return OK;
//}
//
//Status USER_TIM_HandOverLocalList(Node** pMasterList)
//{
//    if (pMasterList == NULL)
//    {
//        return INVALID_PARAMETERS;
//    }
//
//    StateStruct temp;
//
//    while (pLocalTimList != NULL)
//    {
//        temp = List_Pop(&pLocalTimList);
//        List_PushBack(pMasterList, temp);
//    }
//
//    return OK;
//}
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    StateStruct cmdBlock = { 0 };
//
//    static uint8_t changeRouteCounter = 0;
//    static char changeRouteChannel = CHANNEL_A;
//
//    GPIO_PinState gpioBtnStateA = HAL_GPIO_ReadPin(A_BTN_GPIO_Port, A_BTN_Pin);
//    GPIO_PinState gpioBtnStateB = HAL_GPIO_ReadPin(B_BTN_GPIO_Port, B_BTN_Pin);
//
//    if (gpioBtnStateA == GPIO_PIN_RESET && gpioBtnStateB == GPIO_PIN_RESET)
//    {
//        changeRouteCounter++;
//    }
//
//    if (gpioBtnStateA == GPIO_PIN_RESET && gBtnStateA == true)
//    {
//        cmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
//        cmdBlock.channel = CHANNEL_A;
//        cmdBlock.specificator = 0;
//        Status status = USER_TIM_PushCommand(&cmdBlock);
//        gBtnStateA = false;
//    }
//
//    if (gpioBtnStateB == GPIO_PIN_RESET && gBtnStateB == true)
//    {
//        cmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
//        cmdBlock.channel = CHANNEL_B;
//        cmdBlock.specificator = 0;
//        Status status = USER_TIM_PushCommand(&cmdBlock);
//        gBtnStateB = false;
//    }
//
//    if (changeRouteCounter == COUNTS_FOR_CHANGE_ROUTE)
//    {
//        if (changeRouteChannel == CHANNEL_B)
//        {
//            changeRouteChannel = CHANNEL_A;
//        }
//
//        else if (changeRouteChannel == CHANNEL_A)
//        {
//            changeRouteChannel = CHANNEL_B;
//        }
//
//        HAL_GPIO_TogglePin(MCU_PROG_GPIO_Port, MCU_PROG_Pin);
//
//        cmdBlock.state = EXECUTOR_STATE_CHANGE_ROUTE;
//        cmdBlock.channel = changeRouteChannel;
//        cmdBlock.specificator = 0;
//        Status status = USER_TIM_PushCommand(&cmdBlock);
//        changeRouteCounter = 0;
//
//        cmdBlock.state = EXECUTOR_STATE_TOGGLE_CHANNEL;
//        cmdBlock.channel = changeRouteChannel;
//        cmdBlock.specificator = 0;
//        status = USER_TIM_PushCommand(&cmdBlock);
//
//    }
//
//}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
