#include "./../Include/Flash.h"

Status Flash_Init(void)
{
    HAL_StatusTypeDef halStatus = HAL_FLASH_Unlock();
    if(halStatus != HAL_OK)
    {
        return FAIL;
    }
    return OK;
}

Status Flash_DeInit(void)
{
    HAL_StatusTypeDef halStatus = HAL_FLASH_Lock();
    if(halStatus != HAL_OK)
    {
        return FAIL;
    }
    return OK;
}

Status Flash_Erase(uint8_t pageNumber)
{
    if (pageNumber >= MAX_FW_SIZE_IN_PAGES)
    {
        return INVALID_PARAMETERS;
    }

    HAL_StatusTypeDef status;
    uint32_t pageError;

    FLASH_EraseInitTypeDef eraseInit;
    eraseInit.TypeErase   = FLASH_TYPEERASE_PAGES;
    eraseInit.PageAddress = pageNumber * FLASH_PAGE_SIZE + FLASH_USER_START_ADDR;
    eraseInit.NbPages     = 1;

    status = HAL_FLASHEx_Erase(&eraseInit, &pageError);
    if(status != HAL_OK)
    {
        return FAIL;
    }

    return OK;
}

Status Flash_Read(uint32_t offset, uint32_t *pData)
{
    if (pData == NULL)
    {
        return INVALID_PARAMETERS;
    }

    if (offset >= MAX_FW_SIZE_IN_BYTES)
    {
        return INVALID_PARAMETERS;
    }

    *pData = *((volatile uint32_t*)(FLASH_USER_START_ADDR + offset));
    return OK;
}

Status Flash_Write(uint32_t offset, uint32_t data)
{
    if (offset >= MAX_FW_SIZE_IN_BYTES)
    {
        return INVALID_PARAMETERS;
    }

    uint32_t address = FLASH_USER_START_ADDR + offset;
    HAL_StatusTypeDef halStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data);

    if(halStatus != HAL_OK)
    {
        return FAIL;
    }

    return OK;
}
