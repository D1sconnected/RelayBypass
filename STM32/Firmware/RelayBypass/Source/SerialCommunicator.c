#include "SerialCommunicator.h"

typedef struct SerialCommunicatorStruct
{
    char command[SERIAL_RX_BUFFER_SIZE];
    Serial *pSerial;
} SerialCommunicatorStruct;

SerialCommunicator *SerialCommunicator_Create(Serial *pSerial)
{
    if (pSerial == NULL)
    {
        return NULL;
    }

    SerialCommunicator *pSelf = (SerialCommunicator*)calloc(1, sizeof(SerialCommunicatorStruct));
    
    if (pSelf == NULL) 
    {
        return NULL;
    }

    pSelf->pSerial = pSerial;
    return pSelf;
}

void SerialCommunicator_Destroy(SerialCommunicator *pSelf)
{
    if (pSelf == NULL) 
    {
        return;
    }

    Serial_Destroy(pSelf->pSerial);

    free(pSelf);
    pSelf = NULL;
}

Status SerialCommunicator_Handler(SerialCommunicator *pSelf) 
{
    if (pSelf == NULL)
    {
        return INVALID_PARAMETERS;
    }

}