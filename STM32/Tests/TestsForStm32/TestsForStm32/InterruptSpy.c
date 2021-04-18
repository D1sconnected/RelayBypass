#include "InterruptSpy.h"

Status InterruptSpy_PushCommand(Node *pList, StateStruct *pCmd)
{
	if (pList == NULL || pCmd == NULL) 
	{
		return INVALID_PARAMETERS;
	}

	List_PushBack(pList, *pCmd);

	return OK;
}
