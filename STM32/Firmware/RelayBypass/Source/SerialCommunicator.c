#include "SerialCommunicator.h"

typedef struct SerialCommunicatorStruct
{
    char command[32];
} SerialCommunicatorStruct;

SerialCommunicator * SerialCommunicator_Create(void)
{
    return NULL;
}

void SerialCommunicator_Destroy(SerialCommunicator * self)
{
}