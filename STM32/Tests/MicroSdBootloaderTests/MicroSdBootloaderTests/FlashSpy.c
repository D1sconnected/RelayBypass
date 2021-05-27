#include "FlashSpy.h"

static uint32_t *pFlashMemory = NULL;

Status FlashSpy_GetFlashPtr(uint32_t **ppFlashMemory, uint32_t offset)
{
    if (pFlashMemory == NULL || ppFlashMemory == NULL)
    {
        return INVALID_PARAMETERS;
    }

    *ppFlashMemory = &pFlashMemory[offset];
    return OK;
}

Status Flash_Init(void)
{
    pFlashMemory = (uint8_t*)malloc(MAX_FW_SIZE_IN_BYTES);
    if (pFlashMemory == NULL)
    {
        return FAIL;
    }

    return OK;
}

Status Flash_DeInit(void)
{
    if (pFlashMemory == NULL)
    {
        return OK;
    }
    free(pFlashMemory);
    pFlashMemory = NULL;
    return OK;
}

Status Flash_Erase(uint8_t pageNumber) 
{
    if (pFlashMemory == NULL)
    {
        return INVALID_PARAMETERS;
    }
    if (pageNumber >= MAX_FW_SIZE_IN_PAGES)
    {
        return INVALID_PARAMETERS;
    }
    uint32_t offset = pageNumber * PAGE_SIZE_IN_BYTES;
    memset(pFlashMemory + offset, 0xFF, PAGE_SIZE_IN_BYTES);
    return OK;
}

Status Flash_Read(uint32_t offset, uint32_t *pData) 
{
    if (pFlashMemory == NULL || pData == NULL)
    {
        return INVALID_PARAMETERS;
    }
    if (offset >= MAX_FW_SIZE_IN_BYTES)
    {
        return INVALID_PARAMETERS;
    }

    *pData = *(pFlashMemory + offset);

    return OK;
}

Status Flash_Write(uint32_t offset, uint32_t data)
{
    if (pFlashMemory == NULL)
    {
        return INVALID_PARAMETERS;
    }
    /*
    if (offset < FLASH_USER_START_ADDR || offset >= FLASH_USER_START_ADDR + MAX_FW_SIZE_IN_BYTES)
    {
        return INVALID_PARAMETERS;
    }
    */
    //*(pFlashMemory + address) &= data;
    *(pFlashMemory + offset) = data;

    return OK;
}