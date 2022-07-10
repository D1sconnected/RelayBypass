// Serial.h
#ifndef SERIAL_HEADER_FILE_H
#define SERIAL_HEADER_FILE_H

#include "Common.h"
#include <string.h>

#ifdef MIMIC
#include "../../PlatformDependent/Mimic/Include/Interface_Mimic.h"
#endif

#ifdef CONSTRUCTOR
#include "../../PlatformDependent/Constructor/Include/Interface_Constructor.h"
#endif

#define SERIAL_RX_BUFFER_SIZE	32
#define SERIAL_TX_BUFFER_SIZE	256

#define HELP_OUTPUT \
"Command list:\r\n \
    - help\r\n \
    - get: <slot>\r\n \
    - enable: <slot>\r\n \
    - toogle: <slot>\r\n"

#define TOGGLE_OUTPUT \
"Toggle Slot "

#define SWITCH_OUTPUT \
"Switch Slot "

#define GET_OUTPUT \
"Slot "

typedef struct SerialStruct Serial;

Serial *Serial_Create(void);
void Serial_Destroy(Serial *pSelf);


// UART message handler
// pSelf � pointer to object with Serial type
//
// Returns:
// OK � in case of success
// NO_COMMAND � in case of unkown command in rxBuffer 
Status Serial_Handler(Serial *pSelf);

// Handler for <help> command
// pSelf � pointer to object with Serial type
//
// Returns:
// OK � in case of success
// OUT_OF_BOUNDS - in case of response len > txBuffer
Status Serial_HandleHelpCommand(Serial* pSelf);

// Handler for <toogle> command
// pSelf � pointer to object with Serial type
//
// Returns:
// OK � in case of success
// OUT_OF_BOUNDS - in case of response len > txBuffer
Status Serial_HandleToggleCommand(Serial* pSelf);

// Handler for <switch> command
// pSelf � pointer to object with Serial type
//
// Returns:
// OK � in case of success
// OUT_OF_BOUNDS - in case of response len > txBuffer
Status Serial_HandleSwitchCommand(Serial* pSelf);

// Handler for <get> command
// pSelf � pointer to object with Serial type
//
// Returns:
// OK � in case of success
// OUT_OF_BOUNDS - in case of response len > txBuffer
Status Serial_HandleGetCommand(Serial* pSelf);

// Checks that data occured in rxBuffer
// pSelf � pointer to object with Serial type
// 
// Returns:
// OK - in case of data occured in rxBuffer
// NO_DATA � in case there is no data in rxBuffer
Status Serial_ReceiveCmd(Serial *pSelf);

// Send response with UART
// pSelf � pointer to object with Serial type
// pRes � pointer for data to send in response
// 
// Returns:
// OK - in case of data has been successfuly transmitted
// OUT_OF_BOUNDS - in case of response len > txBuffer
Status Serial_SendResponse(Serial *pSelf, char *pRes);

// Clears UART rxBuffer
// pSelf � pointer to object with Serial type
// 
// Returns:
// OK � in case of success
Status Serial_Clear(Serial *pSelf);

#endif
