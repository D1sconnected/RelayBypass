#include "../Include/Loader.h"

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
    uint8_t sdBuf[512];

    for (uint8_t sector = 0; sector < MAX_FW_SIZE_IN_SECTORS; sector++) 
    {
        // Read to sdBuf
        /*
        for (uint16_t byte = 0; byte < 512; byte++) 
        {
            if (*((volatile uint8_t*)(FLASH_USER_START_ADDR + sector * SECTOR_SIZE_IN_BYTES + byte)) != sdBuf[byte])
            {
                break;
            }
        }
        */
    }
}

Status Loader_MainProcess (void) 
{
    Status status;
    uint8_t initCounter = 0;

    // Init microSD in SPI mode
    do 
    {
        status = SDCARD_Init();
    } while (status != OK || initCounter == 10);

    if (status != OK) 
    {
        // Led Blink, then skip update & go to USER_MEM
    }

    // Unlock FLASH 
    status = Flash_Init();
    if (status != OK)
    {
        // Led Blink, then skip update & go to USER_MEM
    }

    // Compare USER_MEM to .bin from microSD


    return status;
}


