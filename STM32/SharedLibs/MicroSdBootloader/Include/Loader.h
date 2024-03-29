// Loader.h
#ifndef LOADER_HEADER_FILE_H
#define LOADER_HEADER_FILE_H

#include "Common.h"
#include "../../sdcard/sdcard.h"
#include "Flash.h"

#ifdef STM32F1_VERSION
#include "../../../Firmware/MicroSdBootloader_STM32F101C4/Core/Inc/main.h"
#endif

#ifdef STM32L1_VERSION
#include "../../../Firmware/MicroSdBootloader_STM32L151C8/Core/Inc/main.h"
#endif

typedef uint8_t Loader;

typedef enum
{
    LOADER_OK                       = 0,
    LOADER_COMPARE_MEMORY_FAILED    = 1,
    LOADER_UPDATE_FIRMWARE_FAILED   = 2,
    LOADER_MAIN_PROCESS_FAILED      = 3
} LoaderStatus;

#define UPDATE_FLAG             0xFEEDBABE
#define LOAD_OFFSET_IN_DWORDS   128

Loader * Loader_Create(void);
void Loader_Destroy(Loader* pSelf);

int Loader_CompareMemory(void);
int Loader_MainProcess(void);
int Loader_UpdateFirmware(void);

#endif
