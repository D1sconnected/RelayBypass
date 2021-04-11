#include "Common.h"

#define SERIAL_RECEIVE_BUFFER_SIZE 32

typedef struct SerialCommunicatorStruct SerialCommunicator;

SerialCommunicator * SerialCommunicator_Create(void);

void SerialCommunicator_Destroy(SerialCommunicator * pSelf);