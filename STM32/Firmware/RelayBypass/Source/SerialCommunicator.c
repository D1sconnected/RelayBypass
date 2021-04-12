#include "SerialCommunicator.h"

typedef struct SerialCommunicatorStruct
{
    char command[SERIAL_RX_BUFFER_SIZE];
} SerialCommunicatorStruct;

SerialCommunicator * SerialCommunicator_Create(void)
{
    SerialCommunicator * pSelf = (SerialCommunicator*)calloc(1, sizeof(SerialCommunicatorStruct));
    
    return pSelf;
}

void SerialCommunicator_Destroy(SerialCommunicator *pSelf)
{
    if (pSelf == NULL) 
    {
        return;
    }

    free(pSelf);
    pSelf = NULL;
}

Status SerialCommunicator_Handler(SerialCommunicator *pSelf) 
{
    if (pSelf == NULL)
    {
        return;
    }

}