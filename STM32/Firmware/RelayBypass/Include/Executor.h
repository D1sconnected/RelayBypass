// Executor.h

#ifndef EXECUTOR_FILE_HEADER_H
#define EXECUTOR_FILE_HEADER_H

#include "Common.h"
#include "List.h"
#include "Serial.h"
#include "Interface.h"

#include "../Core/Inc/gpio.h"
typedef struct ExecutorStruct
{
	Node* pExecutorList;
	//Serial	*pSerial;
} Executor;

Executor * Executor_Create(void);
void Executor_Destroy(Executor *pSelf);

// Executor FSM, which handles commands from pSelf->pExecutorList
// pSelf � pointer to object with Executor type
// 
// Returns:
// OK - in case of success
// INVALID_PARAMETERS - in case pSelf is NULL
Status Executor_Handler(Executor *pSelf);

// Calls all peripheral _UpdateList functions and updating Executor's List
// pSelf � pointer to object with Executor type
//
// Returns:
// OK - in case of success
Status Executor_UpdateList(Executor *pSelf);
#endif
