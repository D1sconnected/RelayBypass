// Loader.h
#ifndef LOADER_HEADER_FILE_H
#define LOADER_HEADER_FILE_H

#include "Common.h"
#include "../Core/Inc/main.h"
#include "./../../SharedLibs/sdcard/sdcard.h"

#define FLASH_USER_START_ADDR       0x08001800
#define SECTOR_SIZE_IN_BYTES        512
#define MAX_FW_SIZE_IN_PAGES        10
#define MAX_FW_SIZE_IN_SECTORS      2 * MAX_FW_SIZE_IN_PAGES

typedef uint8_t Loader;

Loader * Loader_Create(void);
void Loader_Destroy(Loader* pSelf);

Status Loader_CompareMemory(void);
Status Loader_MainProcess(void);
#endif