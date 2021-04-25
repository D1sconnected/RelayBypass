// InterruptSpy.h
#ifndef INTERRUPTESPY_HEADER_FILE_H
#define INTERRUPTESPY_HEADER_FILE_H

#include "Common.h"
#include "List.h"
#include "Interface.h"

Status InterruptSpy_PushCommand(StateStruct *pCmd);
Status InterruptSpy_HandOverLocalList(Node **pMasterList);

#endif