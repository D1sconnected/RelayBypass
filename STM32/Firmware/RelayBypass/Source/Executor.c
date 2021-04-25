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

	static ExecutorState state = -1;
	static StateStruct currentCmdBlock = {0};
	Status status = FAIL;

	status = Executor_UpdateList(pSelf);

	if (status != OK)
	{
		return status;
	}

	currentCmdBlock = List_Pop(&pSelf->pExecutorList);
	state = currentCmdBlock.state;

#ifdef TESTS_ON
	if (state == EXECUTOR_STATE_PREPARE)
	{
		return IN_PREPARE_STATE;
	}
#endif

	switch (state) 
	{
		case EXECUTOR_STATE_SWITCH_CHANNEL:
			return OK;
			break;

	}

 	return status;
}

Status Executor_UpdateList(Executor *pSelf)
{
	// Call _UpdateList for each peripheral
	return InterruptSpy_HandOverLocalList(&pSelf->pExecutorList);
}