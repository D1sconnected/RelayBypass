#include "../Include/Loader.h"

static void Loader_HandleError(int status);
static void Loader_IndicateError (int counter, GPIO_TypeDef *pPort, uint16_t pin);

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

int Loader_CompareMemory(void)
{
    uint32_t sdBuf[128] = {0};
    uint32_t flashBuf = 0;

    int status = 0;

    status = SDCARD_ReadBegin(0x00);
    if (status != OK)
    {
        Loader_HandleError(SDCARD_READ_BEGIN_FAILED);
        return SDCARD_READ_BEGIN_FAILED;
    }

    for (uint8_t sector = 0; sector < MAX_FW_SIZE_IN_SECTORS; sector++) 
    {
        // Read to sdBuf
        status = SDCARD_ReadData((uint8_t*)sdBuf);
        if (status != OK)
        {
            Loader_HandleError(SDCARD_READ_DATA_FAILED);
            return SDCARD_READ_DATA_FAILED;
        }
        
        for (uint8_t dword = 0; dword < 128; dword++) 
        {   
            status = Flash_Read(SECTOR_SIZE_IN_BYTES*sector + 4*dword, &flashBuf);
            if (status != OK)
            {
                Loader_HandleError(FLASH_READ_FAILED);
                return FLASH_READ_FAILED;
            }

            if (sdBuf[dword] != flashBuf) 
            {
                status = SDCARD_ReadEnd();
                if (status != OK)
                {
                    Loader_HandleError(SDCARD_READ_END_FAILED);
                    return SDCARD_READ_END_FAILED;
                }

                return OK;
            }
        }
    }

    status = SDCARD_ReadEnd();
    if (status != OK)
    {
        Loader_HandleError(SDCARD_READ_END_FAILED);
        return SDCARD_READ_END_FAILED;
    }

    return NO_NEED_TO_UPDATE;
}

int Loader_UpdateFirmware(void)
{
    uint32_t sdBuf[128] = { 0 };

    int status = 0;

    status = SDCARD_ReadBegin(0x00);
    if (status != OK)
    {
        Loader_HandleError(SDCARD_READ_BEGIN_FAILED);
        return SDCARD_READ_BEGIN_FAILED;
    }

    for (uint8_t sector = 0; sector < MAX_FW_SIZE_IN_SECTORS; sector++)
    {
        // Read to sdBuf
        status = SDCARD_ReadData((uint8_t*)sdBuf);
        if (status != OK)
        {
            Loader_HandleError(SDCARD_READ_DATA_FAILED);
            return SDCARD_READ_DATA_FAILED;
        }
        HAL_GPIO_TogglePin(MCU_PROG_GPIO_Port, MCU_PROG_Pin);

        for (uint8_t dword = 0; dword < 128; dword++)
        {
            status = Flash_Write(SECTOR_SIZE_IN_BYTES*sector + 4*dword, sdBuf[dword]);
            if (status != OK)
            {
                Loader_HandleError(FLASH_WRITE_FAILED);
                return FLASH_WRITE_FAILED;
            }
        }
    }

    status = SDCARD_ReadEnd();
    if (status != OK)
    {
        Loader_HandleError(SDCARD_READ_END_FAILED);
        return SDCARD_READ_END_FAILED;
    }

    return OK;
}

int Loader_MainProcess (void)
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
        Loader_HandleError(SDCARD_INIT_FAILED);
        return status;
    }

    // Unlock FLASH 
    status = Flash_Init();
    if (status != OK)
    {
        Loader_HandleError(FLASH_INIT_FAILED);
        return status;
    }

    // Compare USER_MEM to .bin from microSD
    status = Loader_CompareMemory();
    if (status != OK)
    {
        Loader_HandleError(LOADER_COMPARE_MEMORY_FAILED);
        return status;
    }

    // Erase Flash
    for (uint8_t page = 0; page < MAX_FW_SIZE_IN_PAGES; page++)
    {
        status = Flash_Erase(page);

        if (status != OK)
        {
            Loader_HandleError(FLASH_ERASE_FAILED);
            return status;
        }
    }

    // Write .bin to USER_MEM
    status = Loader_UpdateFirmware();
    if (status != OK)
    {
        Loader_HandleError(LOADER_UPDATE_FIRMWARE_FAILED);
        return status;
    }

    // Lock FLASH
    status = Flash_DeInit();
    if (status != OK)
    {
        Loader_HandleError(FLASH_DEINIT_FAILED);
    }

    return status;
}

static void Loader_HandleError(int status)
{
    if (status >= SDCARD_STATUS_DEVISOR)
    {
        Loader_IndicateError(status/SDCARD_STATUS_DEVISOR, B_LED_RED_GPIO_Port, B_LED_RED_Pin);
    }

    else
    {
        Loader_IndicateError(status, A_LED_RED_GPIO_Port, A_LED_RED_Pin);
    }
}

static void Loader_IndicateError (int counter, GPIO_TypeDef *pPort, uint16_t pin)
{
    do
    {
        HAL_GPIO_TogglePin(pPort, pin);
        HAL_Delay(100);
        counter--;
    } while (counter != 0);

    HAL_GPIO_WritePin(pPort, pin, GPIO_PIN_RESET);
    // Wait to separate different errors
    HAL_Delay(1000);
}

