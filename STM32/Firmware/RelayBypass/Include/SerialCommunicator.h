#include "Common.h"
#include "Serial.h"

#define HELP_OUTPUT \
"Command list:\r\n \
    - help\r\n \
    - get: <slot>\r\n \
    - enable: <slot>\r\n \
    - toogle: <slot> <count>\r\n"

typedef struct SerialCommunicatorStruct SerialCommunicator;

SerialCommunicator * SerialCommunicator_Create(void);

void SerialCommunicator_Destroy(SerialCommunicator *pSelf);

Status SerialCommunicator_Handler(SerialCommunicator *pSelf);