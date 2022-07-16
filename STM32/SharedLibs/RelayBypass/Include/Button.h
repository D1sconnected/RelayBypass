#ifndef BUTTON_HEADER_FILE_H
#define BUTTON_HEADER_FILE_H

#include "List.h"

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

extern bool gBtnStateA;
extern bool gBtnStateB;
extern bool gSwStateA1;
extern bool gSwStateA3;
extern bool gSwStateB1;
extern bool gSwStateB3;

Status Button_PushCommand(StateStruct *pCmd);
Status Button_HandOverLocalList(Node **pMasterList);
void   Button_Callback (uint16_t GPIO_Pin);

#endif
