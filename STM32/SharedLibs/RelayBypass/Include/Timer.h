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
/* USER CODE END 0 */

#define COUNTS_FOR_CHANGE_ROUTE 50

Status Timer_PushCommand(StateStruct* pCmd);
Status Timer_HandOverLocalList(Node** pMasterList);
void   Timer_Callback (TIM_HandleTypeDef *htim);

#endif
