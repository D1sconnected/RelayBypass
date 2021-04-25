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

TEST(Executor, ShouldHandleChangeRouteState)
{
    // Arrange
    // Set command with SWITCH_CHANNEL state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_CHANGE_ROUTE;
    localCmdBlock.channel = CHANNEL_B;
    localCmdBlock.specificator = NULL;

    // Call InterruptSpy_PushCommand to insert command to pLocalList
    Status status = InterruptSpy_PushCommand(&localCmdBlock);

    // Act
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    // Assert
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
}

TEST(Executor, ShouldHandleSequenceOfStates)
{
    // Arrange
    // Set command with SWITCH_CHANNEL state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_TOGGLE_CHANNEL;
    localCmdBlock.channel = CHANNEL_A;
    localCmdBlock.specificator = NULL;

    // Call InterruptSpy_PushCommand to insert command to pLocalList
    Status status = InterruptSpy_PushCommand(&localCmdBlock);

    // Set command with SWITCH_CHANNEL state
    localCmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
    localCmdBlock.channel = CHANNEL_B;
    localCmdBlock.specificator = NULL;

    // Call InterruptSpy_PushCommand to insert command to pLocalList
    status = InterruptSpy_PushCommand(&localCmdBlock);

    // Act #1
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    // Assert #1
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);

    // Act #2
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    // Assert #2
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);

}

TEST(Executor, ShouldHandleToggleChannelState)
{
    // Arrange
    // Set command with SWITCH_CHANNEL state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_TOGGLE_CHANNEL;
    localCmdBlock.channel = CHANNEL_B;
    localCmdBlock.specificator = NULL;

    // Call InterruptSpy_PushCommand to insert command to pLocalList
    Status status = InterruptSpy_PushCommand(&localCmdBlock);

    // Act
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    // Assert
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
}


TEST(Executor, ShouldHandleSwitchChannelState)
{
    // Arrange
    // Set command with SWITCH_CHANNEL state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
    localCmdBlock.channel = CHANNEL_A;
    localCmdBlock.specificator = NULL;

    // Call InterruptSpy_PushCommand to insert command to pLocalList
    Status status = InterruptSpy_PushCommand(&localCmdBlock);

    // Act
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    // Assert
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
}

TEST(Executor, ShouldHandlePreparationRoutine)
{
    // Arrange
    // Set command with special REPORT state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_PREPARE;
    localCmdBlock.channel = CHANNEL_A;
    localCmdBlock.specificator = NULL;

    // Call InterruptSpy_PushCommand to insert command to pLocalList
    Status status = InterruptSpy_PushCommand(&localCmdBlock);

    // Act
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    // Assert
    // Check FSM returned special REPORT status
    LONGS_EQUAL(IN_PREPARE_STATE, status);
}