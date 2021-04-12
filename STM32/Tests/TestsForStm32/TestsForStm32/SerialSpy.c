// SerialSpy.c

#include "SerialSpy.h"

typedef struct SerialStruct
{
    char rxBuffer[SERIAL_RECEIVE_BUFFER_SIZE];
    char txBuffer[SERIAL_SEND_BUFFER_SIZE];
} SerialStruct;

Status SerialSpy_SetRxBuffer(Serial* pSelf, char* pData, uint32_t len) 
{

}

Status SerialSpy_GetTxBuffer(Serial* pSelf, char** pData) 
{

}