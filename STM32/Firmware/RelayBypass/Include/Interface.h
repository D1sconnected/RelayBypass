// Interface.h
#ifndef INTERFACE_HEADER_FILE_H
#define INTERFACE_HEADER_FILE_H

#include "Common.h"
#include "../Core/Inc/adc.h"
#include "../Core/Inc/gpio.h"

#define FX_OFF false
#define FX_ON  true

#define CHANNEL_A 'A'
#define CHANNEL_B 'B'

#define ADC_MIN_GREEN_BOUND 3723
#define ADC_MIN_RED_BOUND	2482
#define ADC_MIN_BLUE_BOUND	1241

typedef enum 
{
	RED,
	GREEN,
	BLUE
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


// Reads ADC on scpecified channel and identifies LED colour
// channel - specify FX slot to get
// 
// Returns:
// LedColour enum, which can be RED, GREEN or BLUE
LedColour Interface_GetChannel(char channel);

// Change signal path route
// channel - specify wich FX slot will be first
//
// Returns:
// OK – in case of success
// INVALID_FORMAT - in case of incorrect or lack of arguments
Status Interface_ChangeRoute(char channel);

#endif