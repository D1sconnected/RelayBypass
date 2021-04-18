#include "Executor.h"

typedef struct ExecutorStruct
{
	Serial *pSerial;
} ExecutorStruct;

Executor * Executor_Create(void)
{
	Executor *pSelf = (Executor*)calloc(1, sizeof(ExecutorStruct));
	return pSelf;
}

void Executor_Destroy(Serial *pSelf)
{
	if (pSelf == NULL)
	{
		return;
	}

	free(pSelf);
	pSelf = NULL;
}