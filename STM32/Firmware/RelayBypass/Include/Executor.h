// Executor.h
#ifndef EXECUTOR_HEADER_FILE_H
#define EXECUTOR_HEADER_FILE_H

#include "Common.h"
#include "Serial.h"

typedef struct ExecutorStruct Executor;

Executor * Executor_Create(void);
void Executor_Destroy(Executor *pSelf);

#endif
