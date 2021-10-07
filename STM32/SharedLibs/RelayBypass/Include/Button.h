#ifndef BUTTON_HEADER_FILE_H
#define BUTTON_HEADER_FILE_H

#ifdef STM32F1_VERSION
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/gpio.h"
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/tim.h"
#endif

#ifdef STM32L1_VERSION
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/gpio.h"
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/tim.h"
#endif

void Button_Callback (uint16_t GPIO_Pin);
Status USER_GPIO_PushCommand(StateStruct* pCmd);
Status USER_GPIO_HandOverLocalList(Node** pMasterList);

#endif
