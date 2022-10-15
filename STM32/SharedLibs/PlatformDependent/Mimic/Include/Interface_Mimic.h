#ifndef INTERFACE_MIMIC_H
#define INTERFACE_MIMIC_H

#include "../../../RelayBypass/Include/Common.h"
#include "../../../EepromM95/Include/EepromM95.h"

#ifdef MIMIC_F1
#include "../../../../Firmware/RelayBypass_Mimic_STM32F101C4/Core/Inc/gpio.h"
#include "../../../../Firmware/RelayBypass_Mimic_STM32F101C4/Core/Inc/tim.h"
#include "../../../../Firmware/RelayBypass_Mimic_STM32F101C4/Core/Inc/spi.h"
#endif

#define FX_OFF	false
#define FX_ON	true

// Delay time between PHET & RELAY switching in ms
#define BYPASS_DELAY 7

// Digital Pot 
#define MCP41010_RESOLUTION 255
#define MCP41010_CMD_WRITE	0x11

// M95 EEPROM ADDRS
#define EEPROM_A_PROGS_ADDR    0x00
#define EEPROM_B_PROGS_ADDR    0x20
#define EEPROM_INIT_DATA_ADDR  0x40

#define EEPROM_A_FX_STATE_BYTE 0x00
#define EEPROM_B_FX_STATE_BYTE 0x01
#define EEPROM_A_FX_PROG_BYTE  0x02
#define EEPROM_B_FX_PROG_BYTE  0x03


// FV-1 DSP
#define FV1_MAX_PROGS 8
#define FV1_MAX_TIME  1000
#define FV1_MIN_TIME  100
#define FV1_TAP_STEP  100

// Time for events by systick in ms
#define SYSTICK_START_ADC    50
#define SYSTICK_SWITCH_MODE  3000
#define SYSTICK_CHECK_STATUS 15000

#define ADC_TO_MS_COEF      4.096
#define ADC_TO_POT_COEF     16

typedef enum 
{
	RED,
	GREEN,
	BLUE,
	NONE
} LedColour;

extern volatile uint8_t gFxStateA;
extern volatile uint8_t gFxStateB;

extern volatile uint8_t gProgramA;
extern volatile uint8_t gProgramB;
extern volatile uint16_t gTimeA[FV1_MAX_PROGS];
extern volatile uint16_t gTimeB[FV1_MAX_PROGS];

/*
typedef struct InterfaceStruct Interface;

Interface * Interface_Create(void);
void Interface_Destroy(Interface *pSelf);
*/

// Switch selected channel ON/OFF
// channel - specify FX slot to switch
//
// Returns:
// OK � in case of success
// INVALID_FORMAT - in case of incorrect or lack of arguments
Status Interface_SwitchChannel(char channel);

// Toggle RGB LED on selected channel
// channel - specify FX slot to toggle
// 
// Returns:
// OK � in case of success
// INVALID_FORMAT - in case of incorrect or lack of arguments
Status Interface_ToggleChannel(char channel);


// Reads GPIOs on scpecified channel and identifies LED colour
// channel - specify FX slot to get
// 
// Returns:
// LedColour enum, which can be RED, GREEN, BLUE or NONE
LedColour Interface_GetColour(char channel);

// Change signal path route
// channel - specify which FX slot will be first
//
// Returns:
// OK � in case of success
// INVALID_FORMAT - in case of incorrect or lack of arguments
Status Interface_ChangeRoute(char channel);

// Updating LED & RELAY state with HAL_GPIO_WritePin
// channel - specify FX slot to update
// state - specify GPIO_PIN_SET (ON) or GPIO_PIN_RESET (OFF)
//
// Returns:
// None
void Interface_UpdateGpioForSwitch(char channel, GPIO_PinState state);

// Updating DIR RELAY state with HAL_GPIO_WritePin
// state - specify GPIO_PIN_SET (ON) or GPIO_PIN_RESET (OFF)
//
// Returns:
// None
void Interface_UpdateGpioForChange(GPIO_PinState state);

void Interface_UpdateGpioForToggle(char channel);

Status Interface_SwitchProgram(char channel, char specificator);
Status Interface_SwitchEeprom(char channel);
Status Interface_UpdateDigitalPot(char channel, uint8_t value);
Status Interface_UpdateDigitalPotByTap(char channel, uint16_t number);
Status Interface_UpdateDigitalPotByAdc(char channel, uint16_t number);
Status Interface_UpdateMaxTimeForTap(char channel, char specificator);
Status Interface_ToggleForConfigMode(void);
Status Interface_SaveToEeprom(uint16_t addr);
Status Interface_CheckFxAndProgData(void);

#endif
