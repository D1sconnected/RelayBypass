#include "CppUTest/TestHarness.h"

extern "C"
{
#include "SerialCommunicator.h"
}

TEST_GROUP(SerialCommunicator)
{
    SerialCommunicator* pCommunicator = NULL;

    void setup()
    {
        pCommunicator = SerialCommunicator_Create();
    }
    void teardown()
    {
        SerialCommunicator_Destroy(pCommunicator);
    }
};

TEST(SerialCommunicator, ShouldNotBeNull)
{
    CHECK_TRUE(pCommunicator);
}