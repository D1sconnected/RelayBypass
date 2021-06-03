// SdCardSpy.h
#ifndef SDCARDSPY_HEADER_FILE_H
#define SDCARDSPY_HEADER_FILE_H

#include "./../../SharedLibs/sdcard/sdcard.h"

extern uint8_t* pSdMemory;

Status SdcardSpy_InitMemory();
Status SdcardSpy_GetFlashPtr(uint32_t **ppSdMemory, uint32_t offset);

#endif