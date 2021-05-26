#include "SdCardSpy.h"
#include "Flash.h"

static uint8_t *pSdMemory = NULL;
static uint8_t sectorNumber = 0; // ToDo convert to uint32_t

Status SdcardSpy_InitMemory()
{
    pSdMemory = (uint8_t*)malloc(MAX_FW_SIZE_IN_BYTES); // ToDo Double size for reserve copy

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

    *ppSdMemory = (uint32_t*)&pSdMemory[offset];
    return OK;
}

int SDCARD_Init() 
{
    return OK;
}

int SDCARD_ReadBegin(uint32_t blockNum)
{
    sectorNumber = (uint8_t)(blockNum / SECTOR_SIZE_IN_BYTES);
    return 0;
}

int SDCARD_ReadData(uint8_t *buff) 
{
    if (buff == NULL)
    {
        return INVALID_PARAMETERS;
    }

    //*buff = *((pSdMemory + sectorNumber*SECTOR_SIZE_IN_BYTES));
    for (uint16_t byte = 0; byte < SECTOR_SIZE_IN_BYTES; byte++)
    {
        buff[byte] = pSdMemory[byte + sectorNumber*SECTOR_SIZE_IN_BYTES];
    }

    sectorNumber++; // MultipleRead emulation
    return OK;
}

int SDCARD_ReadEnd() 
{
    return 0;
}