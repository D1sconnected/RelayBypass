// Executor.h

#ifndef EXECUTOR_FILE_HEADER_H
#define EXECUTOR_FILE_HEADER_H

#include "Common.h"
#include "List.h"
#include "Serial.h"
#include "Button.h"
#include "Timer.h"

#ifdef MIMIC_F1
#include "../../PlatformDependent/Mimic/Include/Interface_Mimic.h"
#include "../../../Firmware/RelayBypass_Mimic_STM32F101C4/Core/Inc/gpio.h"
#include "../../../Firmware/RelayBypass_Mimic_STM32F101C4/Core/Inc/tim.h"
#endif

#ifdef CONSTRUCTOR_F1
#include "../../PlatformDependent/Constructor/Include/Interface_Constructor.h"
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/gpio.h"
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/tim.h"
#endif


#ifdef CONSTRUCTOR_L1
#include "../../PlatformDependent/Constructor/Include/Interface_Constructor.h"
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/gpio.h"
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/tim.h"
#endif

typedef struct ExecutorStruct
{
	Node *pExecutorList;
	//Serial	*pSerial;
} Executor;

Executor * Executor_Create(void);
void Executor_Destroy(Executor *pSelf);

Status Executor_PushCommand(Executor *pSelf, StateStruct* pCmd);

// Executor FSM, which handles commands from pSelf->pExecutorList
// pSelf � pointer to object with Executor type
// 
// Returns:
// OK - in case of success
// INVALID_PARAMETERS - in case pSelf is NULL
Status Executor_Handler(Executor *pSelf);

// Calls all peripheral _UpdateList functions and updating Executor's List
// pSelf � pointer to object with Executor type
//
// Returns:
// OK - in case of success
Status Executor_UpdateList(Executor *pSelf);
#endif
