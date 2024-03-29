// List.h
#ifndef LIST_HEADER_FILE_H
#define LIST_HEADER_FILE_H

#include "Common.h"

typedef struct
{
	ExecutorState state; // Executor Command
	char channel;		 // Execute on 'A' or 'B' channel
	char specificator;   // Optional condition
	uint16_t number;	 // Optional value
} StateStruct;

typedef struct Node 
{
    StateStruct cmdBlock;
    struct Node *pNext;
} Node;

void List_Push(Node **ppHead, StateStruct command);
StateStruct List_Pop(Node **ppHead);
Node * List_GetLast(Node *pHead);
void List_PushBack(Node **pHead, StateStruct command);

#endif
