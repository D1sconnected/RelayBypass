#include "CppUTest/TestHarness.h"

extern "C"
{
#include "Executor.h"
#include "List.h"
#include "Serial.h"
#include "SerialSpy.h"
#include "InterfaceSpy.h"
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
    // 1. Create executorList
    // 2. Create *pExecutorList
    // 3. Create LocalList  
    // 4. Push new command to LocalList

    // Act
    // Call Executor_Handler with pointer to executorList

    // Assert
    // Check executorList filled with command from LocalList

}
