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

    LONGS_EQUAL(OK, SdcardSpy_InitMemory());
    LONGS_EQUAL(OK, SdcardSpy_GetFlashPtr(&pSdFlash, 0x00));

    LONGS_EQUAL(OK, Flash_Init());
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
    LONGS_EQUAL(OK, status);
}