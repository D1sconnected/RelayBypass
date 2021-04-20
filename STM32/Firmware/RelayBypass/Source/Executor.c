#include "Executor.h"
#include "List.h"

typedef struct ExecutorStruct
{
	Node	*pExecutorList;
	//Serial	*pSerial;
} ExecutorStruct;

Executor * Executor_Create(void)
{
	Executor *pSelf = (Executor*)calloc(1, sizeof(ExecutorStruct));
	return pSelf;
}

void Executor_Destroy(Executor *pSelf)
{
	if (pSelf == NULL)
	{
		return;
	}

	free(pSelf);
	pSelf = NULL;
}

Status Executor_Handler(Executor *pSelf) 
{
	if (pSelf == NULL)
	{
		return INVALID_PARAMETERS;
	}

	static ExecutorState state = EXECUTOR_STATE_UPDATE_LIST;
	Status status = FAIL;

	switch (state) 
	{
		case EXECUTOR_STATE_UPDATE_LIST:
			status = Executor_UpdateList(pSelf);
			break;
	}

	return status;
}

Status Executor_UpdateList(Executor *pSelf)
{
	// Call UpdateList for each peripheral
	pSelf->pExecutorList = InterruptSpy_HandOverLocalList(pSelf->pExecutorList);

	return OK;
}