#include "gpio.h"

static Node *pLocalList = NULL;

Status USER_GPIO_PushCommand(StateStruct *pCmd)
{
	if (pCmd == NULL) 
	{
		return INVALID_PARAMETERS;
	}

	List_PushBack(&pLocalList, *pCmd);

	return OK;
}

Status USER_GPIO_HandOverLocalList(Node **pMasterList)
{
	StateStruct temp;

	if (pLocalList == NULL) 
	{
		return NO_NEW_COMMANDS;
	}

	while (pLocalList != NULL) 
	{
	temp = List_Pop(&pLocalList);
	List_PushBack(pMasterList, temp);
	}

	return OK;
}