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

	static ExecutorState state = EXECUTOR_STATE_PREPARE;
	static StateStruct currentCmdBlock = {0};
	Status status = FAIL;

	switch (state) 
	{
		case EXECUTOR_STATE_PREPARE:
			status = Executor_UpdateList(pSelf);

			if (status != OK) 
			{
				return status;
			}

			currentCmdBlock = List_Pop(&pSelf->pExecutorList);
			state = currentCmdBlock.state;

		case EXECUTOR_STATE_REPORT:
			return REPORT;
	}

	return status;
}

Status Executor_UpdateList(Executor *pSelf)
{
	// Call _UpdateList for each peripheral
	return InterruptSpy_HandOverLocalList(&pSelf->pExecutorList);
}