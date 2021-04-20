// Executor.h

#ifndef EXECUTOR_FILE_HEADER_H
#define EXECUTOR_FILE_HEADER_H

#include "Common.h"
#include "Serial.h"
#include "InterruptSpy.h"

typedef struct ExecutorStruct
{
	Node* pExecutorList;
	//Serial	*pSerial;
} Executor;

Executor * Executor_Create(void);
void Executor_Destroy(Executor *pSelf);

Status Executor_Handler(Executor *pSelf);

#endif
