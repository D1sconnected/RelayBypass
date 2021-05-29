// Loader.h
#ifndef LOADER_HEADER_FILE_H
#define LOADER_HEADER_FILE_H

#include "Common.h"
#include "../Core/Inc/main.h"
#include "./../../SharedLibs/sdcard/sdcard.h"
#include "Flash.h"

typedef uint8_t Loader;

Loader * Loader_Create(void);
void Loader_Destroy(Loader* pSelf);

Status Loader_CompareMemory(void);
Status Loader_MainProcess(void);
Status Loader_UpdateFirmware(void);

#endif