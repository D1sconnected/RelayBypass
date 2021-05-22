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


TEST(Loader, LoaderShouldNotBeNull)
{
    CHECK_TRUE(pLoader);
}
