// Interface.h
#ifndef INTERFACE_HEADER_FILE_H
#define INTERFACE_HEADER_FILE_H

#include "Common.h"

#define FX_OFF false
#define FX_ON  true

#define CHANNEL_A 'A'
#define CHANNEL_B 'B'

typedef struct InterfaceStruct Interface;

Interface * Interface_Create(void);
void Interface_Destroy(Interface *pSelf);


// Switching selected channel exact amount of times
// pSelf – pointer to object with Interface type
//
// Returns:
// OK – in case of success
// INVALID_FORMAT - in case of incorrect or lack of arguments
Status Interface_SwitchChannel(Interface *pSelf, char channel, uint8_t amount);

#endif