// GpioSpyMimic.h
#ifndef GPIOSPYMIMIC_HEADER_FILE_H
#define GPIOSPYMIMIC_HEADER_FILE_H

#ifdef STM32F1_VERSION
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/tim.h"
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/gpio.h"
#endif

#ifdef STM32L1_VERSION
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/tim.h"
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/gpio.h"
#endif

#include "../../../SharedLibs/RelayBypass/Include/Button.h"

GPIO_PinState HAL_GPIO_ReadPin_Mimic(uint8_t GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin_Mimic(uint8_t GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin_Mimic(uint8_t GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback_Mimic(uint16_t GPIO_Pin);

#endif