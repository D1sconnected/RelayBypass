#ifndef TIMER_HEADER_FILE_H
#define TIMER_HEADER_FILE_H


#ifdef STM32F1_VERSION
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/gpio.h"
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/tim.h"
#endif

#ifdef STM32L1_VERSION
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/gpio.h"
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/tim.h"
#endif

#include "Common.h"
#include "List.h"

/* USER CODE BEGIN 0 */
extern bool gBtnStateA;
extern bool gBtnStateB;

static Node* pLocalTimList = NULL;
/* USER CODE END 0 */

TIM_HandleTypeDef htim2;

#define COUNTS_FOR_CHANGE_ROUTE 50

Status USER_TIM_PushCommand(StateStruct* pCmd);
Status USER_TIM_HandOverLocalList(Node** pMasterList);
void Timer_Callback (TIM_HandleTypeDef *htim);

#endif
