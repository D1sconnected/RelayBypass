#include "CppUTest/TestHarness.h"

extern "C"
{
#include "Loader.h"
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

TEST(Loader, ShoudHandleMainProcess)
{
    Status status = Loader_MainProcess();
    LONGS_EQUAL(OK, status);
}

TEST(Loader, ShouldHandleCompareMemory) 
{
    Status status = Loader_CompareMemory();
    LONGS_EQUAL(OK, status);
}