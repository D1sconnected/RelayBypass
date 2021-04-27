#include "../Include/Executor.h"

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
    // Call _UpdateList for each peripheral
    Status status = OK;
    status += USER_GPIO_HandOverLocalList(&pSelf->pExecutorList);
    status += USER_TIM_HandOverLocalList(&pSelf->pExecutorList);

    return status;
}
