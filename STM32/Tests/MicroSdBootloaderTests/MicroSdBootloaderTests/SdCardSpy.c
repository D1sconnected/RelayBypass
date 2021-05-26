#include "SdCardSpy.h"
#include "Flash.h"

static uint8_t *pSdMemory = NULL;

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
    return 0;
}

int SDCARD_ReadData(uint8_t* buff) 
{
    return 0;
}

int SDCARD_ReadEnd() 
{
    return 0;
}