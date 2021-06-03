#include "CppUTest/TestHarness.h"

extern "C"
{
#include "Loader.h"
#include "SdCardSpy.h"
#include "FlashSpy.h"
}

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
    }
};

TEST(Loader, ShouldNotBeNull)
{
    CHECK_TRUE(pLoader);
}

/*
TEST(Loader, ShoudHandleMainProcess)
{
    Status status = Loader_MainProcess();
    LONGS_EQUAL(OK, status);
}
*/

TEST(Loader, ShouldHandleCompareMemoryForIdentical) 
{
    Status status = FAIL;
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

    memcpy(pFlash, pattern, MAX_FW_SIZE_IN_BYTES);
    memcpy(pSdFlash, pattern, MAX_FW_SIZE_IN_BYTES);

    status = Loader_CompareMemory();
    LONGS_EQUAL(NO_NEED_TO_UPDATE, status);
}

TEST(Loader, ShouldHandleCompareMemoryForNotIdentical)
{
    Status status = FAIL;
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

    memcpy(pFlash, pattern, MAX_FW_SIZE_IN_BYTES);
    memcpy(pSdFlash, pattern, MAX_FW_SIZE_IN_BYTES);

    // Corrupt flash
    pFlash[1] = pFlash[10];

    status = Loader_CompareMemory();
    LONGS_EQUAL(OK, status);
}

TEST(Loader, ShouldHandleUpdateFirmware)
{
    Status status = FAIL;
    uint32_t* pFlash = NULL;
    uint32_t* pSdFlash = NULL;

    LONGS_EQUAL(OK, SdcardSpy_GetFlashPtr(&pSdFlash, 0x00));

    LONGS_EQUAL(OK, FlashSpy_GetFlashPtr(&pFlash, 0x00));

    uint8_t pattern[MAX_FW_SIZE_IN_BYTES] = { 0 };

    for (uint32_t byte = 0; byte < MAX_FW_SIZE_IN_BYTES; byte++)
    {
        pattern[byte] = (uint8_t)byte;
    }

    memcpy(pSdFlash, pattern, MAX_FW_SIZE_IN_BYTES);

    for (uint8_t page = 0; page < MAX_FW_SIZE_IN_PAGES; page++)
    {
        status = Flash_Erase(page);
        LONGS_EQUAL(OK, status);
    }

    status = Loader_UpdateFirmware();
    LONGS_EQUAL(OK, status);

    for (uint32_t dword = 0; dword < MAX_FW_SIZE_IN_DWORDS; dword++)
    {
        printf("[%d] - pFlash: %lx, pSdFlash: %lx\n\r", dword, pFlash[dword], pSdFlash[dword]);
        UNSIGNED_LONGS_EQUAL(pFlash[dword], pSdFlash[dword])
    }
}

TEST(Loader, ShouldHandleUpdateWithNoErase)
{
    Status status = FAIL;
    uint32_t* pFlash = NULL;
    uint32_t* pSdFlash = NULL;

    LONGS_EQUAL(OK, SdcardSpy_GetFlashPtr(&pSdFlash, 0x00));

    LONGS_EQUAL(OK, FlashSpy_GetFlashPtr(&pFlash, 0x00));

    uint8_t pattern[MAX_FW_SIZE_IN_BYTES] = { 0 };

    for (uint32_t byte = 0; byte < MAX_FW_SIZE_IN_BYTES; byte++)
    {
        pattern[byte] = (uint8_t)byte;
    }

    memcpy(pSdFlash, pattern, MAX_FW_SIZE_IN_BYTES);

    status = Loader_UpdateFirmware();
    LONGS_EQUAL(OK, status);

    for (uint32_t dword = 0; dword < MAX_FW_SIZE_IN_DWORDS; dword++)
    {
        printf("[%d] - pFlash: %lx, pSdFlash: %lx\n\r", dword, pFlash[dword], pSdFlash[dword]);

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

TEST(Loader, ShouldHandleFlashErase) 
{
    Status status = FAIL;
    uint32_t *pFlash = NULL;

    LONGS_EQUAL(OK, FlashSpy_GetFlashPtr(&pFlash, 0x00));

    for (uint8_t page = 0; page < MAX_FW_SIZE_IN_PAGES; page++)
    {
        status = Flash_Erase(page);
        LONGS_EQUAL(OK, status);
    }

    for (uint32_t dword = 0; dword < MAX_FW_SIZE_IN_DWORDS; dword++)
    {
        printf("[%d] - pFlash: %lx\n\r", dword, pFlash[dword]);
        UNSIGNED_LONGS_EQUAL(pFlash[dword], 0xFFFFFFFF)
    }
}
