#include "CppUTest/TestHarness.h"

extern "C"
{
#include "Executor.h"
#include "List.h"
#include "Serial.h"
#include "SerialSpy.h"
#include "InterfaceSpy.h"
#include "InterruptSpy.h"
}

TEST_GROUP(Executor)
{
    Executor *pExecutor = NULL;

    void setup()
    {
        pExecutor = Executor_Create();
    }
    void teardown()
    {
        Executor_Destroy(pExecutor);
    }
};

TEST(Executor, ShouldNotBeNull)
{
    CHECK_TRUE(pExecutor);
}

TEST(Executor, ShouldHandleUpdateListState)
{
    // Arrange
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
    localCmdBlock.channel = CHANNEL_A;
    localCmdBlock.specificator = NULL;

    // Call InterruptSpy_PushCommand to insert command to pLocalList
    Status status = InterruptSpy_PushCommand(&localCmdBlock);

    // Act
    // Call Executor_Handler with pointer to executorList
    status = Executor_Handler(pExecutor);

    // Assert
    // Check executorList filled with command from LocalList
    CHECK_EQUAL(localCmdBlock.state, pExecutor->pExecutorList->cmdBlock.state);
}