// GpioSpy.h
#ifndef GPIOSPY_HEADER_FILE_H
#define GPIOSPY_HEADER_FILE_H

#ifdef MIMIC_F1
#include "../../../Firmware/RelayBypass_Mimic_STM32F101C4/Core/Inc/gpio.h"
#include "../../../Firmware/RelayBypass_Mimic_STM32F101C4/Core/Inc/tim.h"
#include "stm32f1xx_hal.h"
#endif

#ifdef CONSTRUCTOR_F1
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/gpio.h"
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/tim.h"
#include "stm32f1xx_hal.h"
#endif

#ifdef CONSTRUCTOR_L1
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/tim.h"
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/gpio.h"
#include "stm32l1xx_hal.h"
#endif

#include "../../../SharedLibs/RelayBypass/Include/Button.h"

typedef struct 
{
    GPIO_PinState buttonA;
    GPIO_PinState buttonB;
    GPIO_PinState codeA0;
    GPIO_PinState codeA1;
    GPIO_PinState codeB0;
    GPIO_PinState codeB1;
    GPIO_PinState releA;
    GPIO_PinState releB;
    GPIO_PinState releDir0;
    GPIO_PinState releDir1;
    GPIO_PinState ledRedA;
    GPIO_PinState ledGreenA;
    GPIO_PinState ledBlueA;
    GPIO_PinState ledRedB;
    GPIO_PinState ledGreenB;
    GPIO_PinState ledBlueB;
    GPIO_PinState phet;
    GPIO_PinState mcuProg;
    GPIO_PinState prog0A;
    GPIO_PinState prog1A;
    GPIO_PinState prog2A;
    GPIO_PinState prog0B;
    GPIO_PinState prog1B;
    GPIO_PinState prog2B;
    GPIO_PinState switch1A;
    GPIO_PinState switch3A;
    GPIO_PinState switch1B;
    GPIO_PinState switch3B;
    GPIO_PinState buttonTap;

} EmulatedGpioStatesStruct;

extern EmulatedGpioStatesStruct emulatedGpio;
extern uint8_t                  emulatedDigitalPot;

GPIO_PinState HAL_GPIO_ReadPin(uint8_t GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(uint8_t GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(uint8_t GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout); // ToDo Move to separate SpiSpy?

#endif
