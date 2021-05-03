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
extern bool aBtnState;
extern bool bBtnState;

static Node* pLocalTimList = NULL;
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
  htim2.Init.Period = 50;
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
Status USER_TIM_PushCommand(StateStruct* pCmd)
{
    if (pCmd == NULL)
    {
        return INVALID_PARAMETERS;
    }

    List_PushBack(&pLocalTimList, *pCmd);

    return OK;
}

Status USER_TIM_HandOverLocalList(Node** pMasterList)
{
    StateStruct temp;

    if (pLocalTimList == NULL)
    {
        return NO_NEW_COMMANDS;
    }

    while (pLocalTimList != NULL)
    {
        temp = List_Pop(&pLocalTimList);
        List_PushBack(pMasterList, temp);
    }

    return OK;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    StateStruct cmdBlock = { 0 };

    static uint8_t changeRouteCounter = 0;
    static char changeRouteChannel = CHANNEL_A;

    GPIO_PinState aBtnGpioState = HAL_GPIO_ReadPin(A_BTN_GPIO_Port, A_BTN_Pin);
    GPIO_PinState bBtnGpioState = HAL_GPIO_ReadPin(B_BTN_GPIO_Port, B_BTN_Pin);

    if (aBtnGpioState == GPIO_PIN_RESET && bBtnGpioState == GPIO_PIN_RESET)
    {
        changeRouteCounter++;
    }

    if (aBtnGpioState == GPIO_PIN_RESET && aBtnState == true)
    {
        cmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
        cmdBlock.channel = CHANNEL_A;
        cmdBlock.specificator = 0;
        Status status = USER_TIM_PushCommand(&cmdBlock);
        aBtnState = false;
    }

    if (bBtnGpioState == GPIO_PIN_RESET && bBtnState == true)
    {
        cmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
        cmdBlock.channel = CHANNEL_B;
        cmdBlock.specificator = 0;
        Status status = USER_TIM_PushCommand(&cmdBlock);
        bBtnState = false;
    }

    if (changeRouteCounter == 100)
    {
        if (changeRouteChannel == CHANNEL_B)
        {
            changeRouteChannel = CHANNEL_A;
        }

        else if (changeRouteChannel == CHANNEL_A)
        {
            changeRouteChannel = CHANNEL_B;
        }

        HAL_GPIO_TogglePin(MCU_PROG_GPIO_Port, MCU_PROG_Pin);

        cmdBlock.state = EXECUTOR_STATE_CHANGE_ROUTE;
        cmdBlock.channel = changeRouteChannel;
        cmdBlock.specificator = 0;
        Status status = USER_TIM_PushCommand(&cmdBlock);
        changeRouteCounter = 0;

        cmdBlock.state = EXECUTOR_STATE_TOGGLE_CHANNEL;
        cmdBlock.channel = changeRouteChannel;
        cmdBlock.specificator = 0;
        status = USER_TIM_PushCommand(&cmdBlock);

    }

}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
