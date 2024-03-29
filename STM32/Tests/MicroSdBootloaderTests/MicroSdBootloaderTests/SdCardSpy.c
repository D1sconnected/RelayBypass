#include "SdCardSpy.h"

uint32_t *pSdMemory = NULL;
static uint8_t sectorNumber = 0; // ToDo convert to uint32_t

Status SdcardSpy_InitMemory()
{
    pSdMemory = (uint32_t*)malloc(0x200 + MAX_FW_SIZE_IN_BYTES); // Extra page for UPDATE_FLAG

    if (pSdMemory == NULL)
    {
        return FAIL;
    }

    return OK;
}

Status SdcardSpy_GetFlashPtr(uint32_t **ppSdMemory, uint32_t offset)
{
    if (pSdMemory == NULL || ppSdMemory == NULL)
    {
        return INVALID_PARAMETERS;
    }

    *ppSdMemory = &pSdMemory[offset];
    return OK;
}

int SDCARD_Init() 
{
    return OK;
}

int SDCARD_ReadBegin(uint32_t blockNum)
{
    sectorNumber = (uint8_t)(blockNum);
    return 0;
}

int SDCARD_ReadData(uint8_t *buff) 
{
    if (buff == NULL)
    {
        return INVALID_PARAMETERS;
    }

    //*buff = *((pSdMemory + sectorNumber*SECTOR_SIZE_IN_BYTES));
    uint8_t* pSdMemoryByte = (uint8_t*)pSdMemory;
    for (uint16_t byte = 0; byte < SECTOR_SIZE_IN_BYTES; byte++)
    {
        buff[byte] = pSdMemoryByte[byte + sectorNumber*SECTOR_SIZE_IN_BYTES];
    }

    sectorNumber++; // MultipleRead emulation
    return OK;
}

int SDCARD_ReadEnd() 
{
    return 0;
}