#include "../Include/List.h"

void List_Push(Node **ppHead, StateStruct command)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->cmdBlock = command;
    newNode->pNext = (*ppHead);
    (*ppHead) = newNode;
}

StateStruct List_Pop(Node **ppHead)
{
    Node *previousNode = NULL;
    StateStruct command;

    if (*ppHead == NULL)
    {
        return;
    }

    previousNode = (*ppHead);
    command = previousNode->cmdBlock;
    (*ppHead) = (*ppHead)->pNext;
    free(previousNode);

    return command;
}


Node * List_GetLast(Node *pHead) 
{
    if (pHead == NULL) 
    {
        return NULL;
    }

    while (pHead->pNext) 
    {
        pHead = pHead->pNext;
    }

    return pHead;
}

void List_PushBack(Node **pHead, StateStruct command) 
{
    Node *lastNode = List_GetLast(*pHead);

    if (lastNode == NULL)
    {
        List_Push(pHead, command);
    }

    else if (lastNode != NULL) 
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->cmdBlock = command;
        newNode->pNext = NULL;
        lastNode->pNext = newNode;
    }

}
