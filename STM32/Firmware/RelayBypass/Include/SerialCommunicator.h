#include "Common.h"
#include "Serial.h"

typedef struct SerialCommunicatorStruct SerialCommunicator;

SerialCommunicator * SerialCommunicator_Create(void);

void SerialCommunicator_Destroy(SerialCommunicator *pSelf);

Status SerialCommunicator_Handler(SerialCommunicator *pSelf);