#ifndef SDCARDSPY_HEADER_FILE_H
#define SDCARDSPY_HEADER_FILE_H

#include "./../../SharedLibs/sdcard/sdcard.h"
#include "../../SharedLibs/MicroSdBootloader/Include/Flash.h"

extern uint32_t *pSdMemory;

Status SdcardSpy_InitMemory();
Status SdcardSpy_GetFlashPtr(uint32_t **ppSdMemory, uint32_t offset);

#endif