#include "Common.h"

typedef struct SerialCommunicatorStruct SerialCommunicator;

SerialCommunicator * SerialCommunicator_Create(void);

void SerialCommunicator_Destroy(SerialCommunicator * self);