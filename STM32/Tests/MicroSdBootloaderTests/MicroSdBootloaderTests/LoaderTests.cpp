#include "CppUTest/TestHarness.h"

extern "C"
{
#ifdef STM32F1_VERSION
#include "../../../Firmware/MicroSdBootloader_STM32F101C4/Core/Inc/main.h"
#include "stm32f1xx_hal.h"
#endif

#ifdef STM32L1_VERSION
#include "../../../Firmware/MicroSdBootloader_STM32L151C8/Core/Inc/main.h"
#include "stm32l1xx_hal.h"
#endif

#include "../../SharedLibs/MicroSdBootloader/Include/Loader.h"
#include "SdCardSpy.h"
#include "FlashSpy.h"
#include "GpioSpy.h"
}

//#define DEBUG_PRINT

TEST_GROUP(Loader)
{
    Loader *pLoader = NULL;

    void setup()
    {
        pLoader = Loader_Create();
        LONGS_EQUAL(OK, Flash_Init());
        LONGS_EQUAL(OK, SdcardSpy_InitMemory());
    }
    void teardown()
    {
        Loader_Destroy(pLoader);

        free(pFlashMemory);
        free(pSdMemory);
        pFlashMemory = NULL;
        pSdMemory = NULL;

    }
};

TEST(Loader, Should_Not_Be_Null)
{
    printf("\n\r------------------------------------------------------------------------\n\r");
    printf("[%s]\n\r", __FUNCTION__);
    printf("------------------------------------------------------------------------\n\r");

    CHECK_TRUE(pLoader);
}

TEST(Loader, Should_Handle_Main_Process)
{
    printf("\n\r------------------------------------------------------------------------\n\r");
    printf("[%s]\n\r", __FUNCTION__);
    printf("------------------------------------------------------------------------\n\r");

    int status = FAIL;
    uint32_t* pFlash = NULL;
    uint32_t* pSdFlash = NULL;

    LONGS_EQUAL(OK, SdcardSpy_GetFlashPtr(&pSdFlash, 0x00));

    LONGS_EQUAL(OK, FlashSpy_GetFlashPtr(&pFlash, 0x00));

    // Allocate Test Pattern, sizeof 10 kB

    uint8_t pattern[MAX_FW_SIZE_IN_BYTES] = { 0 };

    for (uint32_t byte = 0; byte < MAX_FW_SIZE_IN_BYTES; byte++)
    {
        pattern[byte] = (uint8_t)byte;
    }

    pSdFlash[0] = UPDATE_FLAG;
    memcpy(pFlash, pattern, MAX_FW_SIZE_IN_BYTES);
    memcpy(&pSdFlash[LOAD_OFFSET_IN_DWORDS], pattern, MAX_FW_SIZE_IN_BYTES);

    // Corrupt flash
    pFlash[10] = pFlash[20];

    status = Loader_MainProcess();
    LONGS_EQUAL(OK, status);
}

TEST(Loader, Should_Compare_Memory_For_Identical) 
{
    printf("\n\r------------------------------------------------------------------------\n\r");
    printf("[%s]\n\r", __FUNCTION__);
    printf("------------------------------------------------------------------------\n\r");

    int status = FAIL;
    uint32_t *pFlash = NULL;
    uint32_t *pSdFlash = NULL;

    LONGS_EQUAL(OK, SdcardSpy_GetFlashPtr(&pSdFlash, 0x00));

    LONGS_EQUAL(OK, FlashSpy_GetFlashPtr(&pFlash, 0x00));

    // Allocate Test Pattern, sizeof 10 kB
    
    uint8_t pattern[MAX_FW_SIZE_IN_BYTES]  = { 0 };

    for (uint32_t byte = 0; byte < MAX_FW_SIZE_IN_BYTES; byte++) 
    {
        pattern[byte] = (uint8_t)byte;
    }

    pSdFlash[0] = UPDATE_FLAG;
    memcpy(pFlash, pattern, MAX_FW_SIZE_IN_BYTES);
    memcpy(&pSdFlash[LOAD_OFFSET_IN_DWORDS], pattern, MAX_FW_SIZE_IN_BYTES);

    status = Loader_CompareMemory();
    LONGS_EQUAL(NO_NEED_TO_UPDATE, status);
}

TEST(Loader, Should_Compare_Memory_For_Not_Identical)
{
    printf("\n\r------------------------------------------------------------------------\n\r");
    printf("[%s]\n\r", __FUNCTION__);
    printf("------------------------------------------------------------------------\n\r");

    int status = FAIL;
    uint32_t *pFlash = NULL;
    uint32_t *pSdFlash = NULL;

    LONGS_EQUAL(OK, SdcardSpy_GetFlashPtr(&pSdFlash, 0x00));

    LONGS_EQUAL(OK, FlashSpy_GetFlashPtr(&pFlash, 0x00));

    // Allocate Test Pattern, sizeof 10 kB

    uint8_t pattern[MAX_FW_SIZE_IN_BYTES] = { 0 };

    for (uint32_t byte = 0; byte < MAX_FW_SIZE_IN_BYTES; byte++)
    {
        pattern[byte] = (uint8_t)byte;
    }

    pSdFlash[0] = UPDATE_FLAG;
    memcpy(pFlash, pattern, MAX_FW_SIZE_IN_BYTES);
    memcpy(&pSdFlash[LOAD_OFFSET_IN_DWORDS], pattern, MAX_FW_SIZE_IN_BYTES);

    // Corrupt flash
    pFlash[1] = pFlash[10];

    status = Loader_CompareMemory();
    LONGS_EQUAL(OK, status);
}

TEST(Loader, Should_Update_Firmware)
{
    printf("\n\r------------------------------------------------------------------------\n\r");
    printf("[%s]\n\r", __FUNCTION__);
    printf("------------------------------------------------------------------------\n\r");

    int status = FAIL;
    uint32_t *pFlash = NULL;
    uint32_t *pSdFlash = NULL;

    LONGS_EQUAL(OK, SdcardSpy_GetFlashPtr(&pSdFlash, 0x00));
    LONGS_EQUAL(OK, FlashSpy_GetFlashPtr(&pFlash, 0x00));

    pSdFlash[0] = UPDATE_FLAG;
    uint8_t *pByteSdFlash = (uint8_t*)(&pSdFlash[LOAD_OFFSET_IN_DWORDS]);

    for (uint32_t byte = 0; byte < MAX_FW_SIZE_IN_BYTES; byte++)
    {
        pByteSdFlash[byte] = (uint8_t)byte;
    }

    for (uint8_t page = 0; page < MAX_FW_SIZE_IN_PAGES; page++)
    {
        status = Flash_Erase(page);
        LONGS_EQUAL(OK, status);
    }

    status = Loader_UpdateFirmware();
    LONGS_EQUAL(OK, status);

    for (uint32_t dword = 0; dword < MAX_FW_SIZE_IN_DWORDS; dword++)
    {
        #ifdef DEBUG_PRINT
        printf("[%d] - pFlash: %lx, pSdFlash: %lx\n\r", dword, pFlash[dword], pSdFlash[LOAD_OFFSET_IN_DWORDS+dword]);
        #endif
        UNSIGNED_LONGS_EQUAL(pFlash[dword], pSdFlash[LOAD_OFFSET_IN_DWORDS+dword])
    }
}

TEST(Loader, Should_Not_Update_With_No_Erase)
{
    printf("\n\r------------------------------------------------------------------------\n\r");
    printf("[%s]\n\r", __FUNCTION__);
    printf("------------------------------------------------------------------------\n\r");

    int status = FAIL;
    uint32_t *pFlash = NULL;
    uint32_t *pSdFlash = NULL;

    LONGS_EQUAL(OK, SdcardSpy_GetFlashPtr(&pSdFlash, 0x00));
    LONGS_EQUAL(OK, FlashSpy_GetFlashPtr(&pFlash, 0x00));

    pSdFlash[0] = UPDATE_FLAG;
    uint8_t* pByteSdFlash = (uint8_t*)(&pSdFlash[LOAD_OFFSET_IN_DWORDS]);

    for (uint32_t byte = 0; byte < MAX_FW_SIZE_IN_BYTES; byte++)
    {
        pByteSdFlash[byte] = (uint8_t)byte;
    }

    status = Loader_UpdateFirmware();
    LONGS_EQUAL(OK, status);

    for (uint32_t dword = 0; dword < MAX_FW_SIZE_IN_DWORDS; dword++)
    {
        #ifdef DEBUG_PRINT
        printf("[%d] - pFlash: %lx, pSdFlash: %lx\n\r", dword, pFlash[dword], pSdFlash[dword]);
        #endif
        if (pFlash[dword] != pSdFlash[dword]) 
        {
            status = OK;
        }

        else 
        {
            status = FAIL;
        }

        LONGS_EQUAL(OK, status);
    }
}

TEST(Loader, Should_Not_Update_With_No_Update_Flag)
{
    printf("\n\r------------------------------------------------------------------------\n\r");
    printf("[%s]\n\r", __FUNCTION__);
    printf("------------------------------------------------------------------------\n\r");

    int status = FAIL;
    uint32_t* pFlash = NULL;
    uint32_t* pSdFlash = NULL;

    LONGS_EQUAL(OK, SdcardSpy_GetFlashPtr(&pSdFlash, 0x00));
    LONGS_EQUAL(OK, FlashSpy_GetFlashPtr(&pFlash, 0x00));

    pSdFlash[0] = 0x00000000;
    uint8_t* pByteSdFlash = (uint8_t*)(&pSdFlash[LOAD_OFFSET_IN_DWORDS]);

    for (uint32_t byte = 0; byte < MAX_FW_SIZE_IN_BYTES; byte++)
    {
        pByteSdFlash[byte] = (uint8_t)byte;
    }

    status = Loader_CompareMemory();
    LONGS_EQUAL(NO_NEED_TO_UPDATE, status);
}

TEST(Loader, Should_Handle_FlashErase) 
{
    printf("\n\r------------------------------------------------------------------------\n\r");
    printf("[%s]\n\r", __FUNCTION__);
    printf("------------------------------------------------------------------------\n\r");

    int status = FAIL;
    uint32_t *pFlash = NULL;

    LONGS_EQUAL(OK, FlashSpy_GetFlashPtr(&pFlash, 0x00));

    for (uint8_t page = 0; page < MAX_FW_SIZE_IN_PAGES; page++)
    {
        status = Flash_Erase(page);
        LONGS_EQUAL(OK, status);
    }

    for (uint32_t dword = 0; dword < MAX_FW_SIZE_IN_DWORDS; dword++)
    {
        #ifdef DEBUG_PRINT
        printf("[%d] - pFlash: %lx\n\r", dword, pFlash[dword]);
        #endif
        UNSIGNED_LONGS_EQUAL(pFlash[dword], 0xFFFFFFFF)
    }
}