#include "SerialCommunicator.h"

typedef struct SerialCommunicatorStruct
{
    char command[32];
} SerialCommunicatorStruct;

SerialCommunicator * SerialCommunicator_Create(void)
{
    SerialCommunicator * pSelf = (SerialCommunicator*)calloc(1, sizeof(SerialCommunicatorStruct));
    
    return pSelf;
}

void SerialCommunicator_Destroy(SerialCommunicator * pSelf)
{
    if (pSelf == NULL) 
    {
        return;
        //return INVALID_PARAMETERS;
    }

    free(pSelf);
    pSelf = NULL;
}