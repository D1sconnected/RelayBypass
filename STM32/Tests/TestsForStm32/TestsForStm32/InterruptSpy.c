#include "InterruptSpy.h"

//static Node *pLocalList = NULL;

Status InterruptSpy_PushCommand(StateStruct *pCmd)
{
	if (pCmd == NULL) 
	{
		return INVALID_PARAMETERS;
	}

	Node *pLocalList = NULL;
	List_PushBack(&pLocalList, *pCmd);

	return OK;
}

Status InterruptSpy_HandOverLocalList(Node* pMasterList)
{
	if (pMasterList == NULL)
	{
		return INVALID_PARAMETERS;
	}

	StateStruct temp;
	Node* pLocalList = NULL;
	while (pLocalList != NULL) 
	{
	temp = List_Pop(pLocalList);
	List_PushBack(pMasterList, temp);
	}

	return OK;
}