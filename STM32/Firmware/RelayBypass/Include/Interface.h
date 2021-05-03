// Interface.h
#ifndef INTERFACE_HEADER_FILE_H
#define INTERFACE_HEADER_FILE_H

#include "Common.h"
#include "../Core/Inc/main.h"
#include "../Core/Inc/gpio.h"

#define FX_OFF false
#define FX_ON  true

// Delay time between PHET & RELAY switching in ms
#define BYPASS_DELAY 7

typedef enum 
{
	RED,
	GREEN,
	BLUE,
	NONE
} LedColour;

/*
typedef struct InterfaceStruct Interface;

Interface * Interface_Create(void);
void Interface_Destroy(Interface *pSelf);
*/

// Switch selected channel ON/OFF
// channel - specify FX slot to switch
//
// Returns:
// OK – in case of success
// INVALID_FORMAT - in case of incorrect or lack of arguments
Status Interface_SwitchChannel(char channel);

// Toggle RGB LED on selected channel
// channel - specify FX slot to toggle
// 
// Returns:
// OK – in case of success
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
// OK – in case of success
// INVALID_FORMAT - in case of incorrect or lack of arguments
Status Interface_ChangeRoute(char channel);

// Updating LED & RELAY state with HAL_GPIO_WritePin
// channel - specify FX slot to update
// colour - specify LED colour of FX slot
// state - specify GPIO_PIN_SET (ON) or GPIO_PIN_RESET (OFF)
//
// Returns:
// None
void Interface_UpdateGpioForSwitch(char channel, LedColour colour, GPIO_PinState state);

// Updating DIR RELAY state with HAL_GPIO_WritePin
// state - specify GPIO_PIN_SET (ON) or GPIO_PIN_RESET (OFF)
//
// Returns:
// None
void Interface_UpdateGpioForChange(GPIO_PinState state);

#endif