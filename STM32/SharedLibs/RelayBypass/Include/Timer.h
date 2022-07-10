#ifndef TIMER_HEADER_FILE_H
#define TIMER_HEADER_FILE_H

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

#include "Common.h"
#include "List.h"
#include "Button.h"

#define COUNTS_FOR_CHANGE_ROUTE 50

Status Timer_PushCommand(StateStruct* pCmd);
Status Timer_HandOverLocalList(Node** pMasterList);
void   Timer_Callback (TIM_HandleTypeDef *htim);

#endif
