// InterfaceSpy.h
#ifndef INTERFACESPY_HEADER_FILE_H
#define INTERFACESPY_HEADER_FILE_H

#include "Common.h"
#include "Interface.h"

#define INTERFACE_SPY_GREEN_VALUE	3800
#define INTERFACE_SPY_RED_VALUE		2500
#define INTERFACE_SPY_BLUE_VALUE	1300

LedColour Interface_GetChannel(char channel);

#endif