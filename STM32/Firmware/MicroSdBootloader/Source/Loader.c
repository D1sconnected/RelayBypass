#include "../Include/Loader.h"

static void Loader_IndicateError (int status);

Loader * Loader_Create(void)
{
    Loader *pSelf = (Loader*)calloc(1, sizeof(Loader));
    return pSelf;
}

void Loader_Destroy(Loader *pSelf)
{
    if (pSelf == NULL)
    {
        return;
    }

    free(pSelf);
    pSelf = NULL;
}

Status Loader_CompareMemory(void)
{
    uint32_t sdBuf[128] = {0};
    uint32_t flashBuf = 0;

    SDCARD_ReadBegin(0x00);

    for (uint8_t sector = 0; sector < MAX_FW_SIZE_IN_SECTORS; sector++) 
    {
        // Read to sdBuf
        SDCARD_ReadData((uint8_t*)sdBuf);
        
        for (uint8_t dword = 0; dword < 128; dword++) 
        {   
            Flash_Read(sector*SECTOR_SIZE_IN_BYTES + 4*dword, &flashBuf);

            if (sdBuf[dword] != flashBuf) 
            {
                SDCARD_ReadEnd();
                return OK;
            }
        }
    }

    SDCARD_ReadEnd();
    return NO_NEED_TO_UPDATE;
}

Status Loader_UpdateFirmware(void) 
{
    uint32_t sdBuf[128] = { 0 };

    SDCARD_ReadBegin(0x00);

    for (uint8_t sector = 0; sector < MAX_FW_SIZE_IN_SECTORS; sector++)
    {
        // Read to sdBuf
        SDCARD_ReadData((uint8_t*)sdBuf);
        HAL_GPIO_TogglePin(MCU_PROG_GPIO_Port, MCU_PROG_Pin);

        for (uint8_t dword = 0; dword < 128; dword++)
        {
            Flash_Write(sector*SECTOR_SIZE_IN_BYTES + 4*dword, sdBuf[dword]);
        }
    }

    SDCARD_ReadEnd();
    return OK;
}

Status Loader_MainProcess (void) 
{
    Status status;
    uint8_t initCounter = 0;

    // Init microSD in SPI mode
    do 
    {
        status = SDCARD_Init();
        initCounter++;
    } while (status != OK && initCounter != 10);

    if (status != OK) 
    {
        // Led Blink, then skip update & go to USER_MEM
        return FAIL;
    }

    // Unlock FLASH 
    status = Flash_Init();
    if (status != OK)
    {
        Loader_IndicateError(FLASH_INIT_FAILED);
        return status;
    }

    // Compare USER_MEM to .bin from microSD
    status = Loader_CompareMemory();
    if (status != OK)
    {
        Loader_IndicateError(LOADER_COMPARE_MEMORY_FAILED);
        return status;
    }

    // Erase Flash
    for (uint8_t page = 0; page < MAX_FW_SIZE_IN_PAGES; page++)
    {
        status = Flash_Erase(page);

        if (status != OK)
        {
            Loader_IndicateError(FLASH_ERASE_FAILED);
            return status;
        }
    }

    // Write .bin to USER_MEM
    status = Loader_UpdateFirmware();
    if (status != OK)
    {
        Loader_IndicateError(LOADER_UPDATE_FIRMWARE_FAILED);
        return status;
    }

    // Lock FLASH
    status = Flash_DeInit();
    if (status != OK)
    {
        Loader_IndicateError(FLASH_DEINIT_FAILED);
    }

    return status;
}

static void Loader_IndicateError (int counter)
{
    do
    {
        HAL_GPIO_TogglePin(A_LED_RED_GPIO_Port, A_LED_RED_Pin);
        HAL_Delay(100);
        counter--;
    } while (counter != 0);
}
