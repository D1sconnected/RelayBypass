#include "../Include/Executor.h"

Executor * Executor_Create(void)
{
    Executor *pSelf = (Executor*)calloc(1, sizeof(Executor));
    pSelf->pExecutorList = NULL;
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
    Status status = Executor_UpdateList(pSelf);

    if (status != OK)
    {
        return status;
    }

    currentCmdBlock = List_Pop(&pSelf->pExecutorList);
    state = currentCmdBlock.state;

    switch (state) 
    {
        case EXECUTOR_STATE_SWITCH_CHANNEL:
        {
            status = Interface_SwitchChannel(currentCmdBlock.channel);
            return status;
        }
        break;

        case EXECUTOR_STATE_TOGGLE_CHANNEL:
        {
            status = Interface_ToggleChannel(currentCmdBlock.channel);
            return status;
        }
        break;

        case EXECUTOR_STATE_CHANGE_ROUTE:
        {
            status = Interface_ChangeRoute(currentCmdBlock.channel);
            return status;
        }
        break;
    }

     return NO_COMMAND;
}

Status Executor_UpdateList(Executor *pSelf)
{
    if (pSelf == NULL)
    {
        return INVALID_PARAMETERS;
    }

    // Call HandOverLocalList for each peripheral
    Status status = OK;
    status += Button_HandOverLocalList(&pSelf->pExecutorList);
    status += Timer_HandOverLocalList(&pSelf->pExecutorList);

    return status;
}
