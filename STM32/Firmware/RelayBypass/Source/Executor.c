#include "Executor.h"
#include "List.h"


Executor * Executor_Create(void)
{
	Executor *pSelf = (Executor*)calloc(1, sizeof(Executor));
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
	return InterruptSpy_HandOverLocalList(&pSelf->pExecutorList);
}