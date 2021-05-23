#include "Flash.h"

Status FlashSpy_GetFlashPtr(uint32_t **ppFlashMemory, uint32_t address);

static uint8_t *pFlashMemory = NULL;

Status FlashSpy_GetFlashPtr(uint32_t **ppFlashMemory, uint32_t address)
{
    if (pFlashMemory == NULL)
    {
        return INVALID_PARAMETERS;
    }
    if (ppFlashMemory == NULL || address < FLASH_USER_START_ADDR || address >= FLASH_USER_START_ADDR + MAX_FW_SIZE_IN_BYTES)
    {
        return INVALID_PARAMETERS;
    }
    *ppFlashMemory = (uint32_t*)&pFlashMemory[address];
    return OK;
}

Status Flash_Init(void)
{
    pFlashMemory = (uint8_t*)malloc(MAX_FW_SIZE_IN_BYTES);
    if (pFlashMemory == NULL)
    {
        return FAIL;
    }
    //memset(pFlashMemory, 0xFF, MAX_FW_SIZE_IN_BYTES);
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
    *pData = *(uint32_t*)(pFlashMemory + offset);
    return OK;
}

Status Flash_Write(uint32_t address, uint32_t data)
{
    if (pFlashMemory == NULL)
    {
        return INVALID_PARAMETERS;
    }
    if (address < FLASH_USER_START_ADDR || address >= FLASH_USER_START_ADDR + MAX_FW_SIZE_IN_BYTES)
    {
        return INVALID_PARAMETERS;
    }

    *(uint32_t*)(pFlashMemory + address) &= data;
    return OK;
}