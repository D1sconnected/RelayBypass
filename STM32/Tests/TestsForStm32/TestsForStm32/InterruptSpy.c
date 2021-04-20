#include "InterruptSpy.h"

static Node *pLocalList = NULL;

Status InterruptSpy_PushCommand(StateStruct *pCmd)
{
	if (pCmd == NULL) 
	{
		return INVALID_PARAMETERS;
	}

	List_PushBack(&pLocalList, *pCmd);

	return OK;
}

Status InterruptSpy_HandOverLocalList(Node **pMasterList)
{
	StateStruct temp;

	while (pLocalList != NULL) 
	{
	temp = List_Pop(&pLocalList);
	List_PushBack(pMasterList, temp);
	}

	return OK;
}