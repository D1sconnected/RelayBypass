// FlashSpy.h
#ifndef FLASHSPY_HEADER_FILE_H
#define FLASHSPY_HEADER_FILE_H

#include "Flash.h"
#include "stdio.h"

extern uint32_t* pFlashMemory;

Status FlashSpy_GetFlashPtr(uint32_t **ppFlashMemory, uint32_t offset);

#endif