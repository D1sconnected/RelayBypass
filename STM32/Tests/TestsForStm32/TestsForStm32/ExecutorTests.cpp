#include "CppUTest/TestHarness.h"

extern "C"
{
#include "main.h"
#include "Executor.h"
#include "List.h"
#include "Serial.h"
#include "SerialSpy.h"
#include "GpioSpy.h"
#include "TimSpy.h"
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

TEST(Executor, ShouldHandleSequenceOfSwitchChannelFromButtons)
{
    // Arange 
    // Call HAL_GPIO_EXTI_Callback
    emulatedGpio.buttonA = GPIO_PIN_RESET;
    emulatedGpio.buttonB = GPIO_PIN_SET;
    HAL_GPIO_EXTI_Callback(A_BTN_Pin);

    // Call HAL_TIM_PeriodElapsedCallback
    HAL_TIM_PeriodElapsedCallback(&htim2);

    // Act
    // Call Executor_Handler with pointer to Executor's List
    Status status = Executor_Handler(pExecutor);

    // Assert
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);

    // Arange 
    // Call HAL_GPIO_EXTI_Callback
    emulatedGpio.buttonA = GPIO_PIN_SET;
    emulatedGpio.buttonB = GPIO_PIN_RESET;
    HAL_GPIO_EXTI_Callback(B_BTN_Pin);

    // Call HAL_TIM_PeriodElapsedCallback
    HAL_TIM_PeriodElapsedCallback(&htim2);

    // Act
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    // Assert
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);

    // Arange 
    // Call HAL_GPIO_EXTI_Callback
    emulatedGpio.buttonA = GPIO_PIN_RESET;
    emulatedGpio.buttonB = GPIO_PIN_SET;
    HAL_GPIO_EXTI_Callback(A_BTN_Pin);

    // Call HAL_TIM_PeriodElapsedCallback
    HAL_TIM_PeriodElapsedCallback(&htim2);

    // Act
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    // Assert
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
}

TEST(Executor, ShouldHandleSwitchChannelFromButtonB)
{
    // Arange 
    // Call HAL_GPIO_EXTI_Callback
    emulatedGpio.buttonA = GPIO_PIN_SET;
    emulatedGpio.buttonB = GPIO_PIN_RESET;
    HAL_GPIO_EXTI_Callback(B_BTN_Pin);

    // Call HAL_TIM_PeriodElapsedCallback
    HAL_TIM_PeriodElapsedCallback(&htim2);

    // Act
    // Call Executor_Handler with pointer to Executor's List
    Status status = Executor_Handler(pExecutor);

    // Assert
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
}

TEST(Executor, ShouldHandleSwitchChannelFromButtonA)
{
    // Arange 
    // Call HAL_GPIO_EXTI_Callback
    emulatedGpio.buttonA = GPIO_PIN_RESET;
    emulatedGpio.buttonB = GPIO_PIN_SET;
    HAL_GPIO_EXTI_Callback(A_BTN_Pin);

    // Call HAL_TIM_PeriodElapsedCallback
    HAL_TIM_PeriodElapsedCallback(&htim2);

    // Act
    // Call Executor_Handler with pointer to Executor's List
    Status status = Executor_Handler(pExecutor);

    // Assert
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
}

TEST(Executor, ShouldHandleChangeRouteState)
{
    // Arrange
    // Set command with SWITCH_CHANNEL state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_CHANGE_ROUTE;
    localCmdBlock.channel = CHANNEL_B;
    localCmdBlock.specificator = NULL;

    // Call USER_GPIO_PushCommand to insert command to pLocalList
    Status status = USER_GPIO_PushCommand(&localCmdBlock);

    // Act
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    // Assert
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
}

TEST(Executor, ShouldHandleSequenceOfStates)
{
    //----------Arrange----------//
    // Set all emulatedGpio to GPIO_PIN_RESET
    memset(&emulatedGpio, GPIO_PIN_RESET, sizeof(EmulatedGpioStatesStruct));
    // Set DISTORTION/FUZZ code for Channel A
    emulatedGpio.codeA0 = GPIO_PIN_RESET;
    emulatedGpio.codeA1 = GPIO_PIN_SET;
    // Set OTHER code for Channel B
    emulatedGpio.codeB0 = GPIO_PIN_SET;
    emulatedGpio.codeB1 = GPIO_PIN_RESET;

    // Set command with SWITCH_CHANNEL state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
    localCmdBlock.channel = CHANNEL_A;
    localCmdBlock.specificator = NULL;

    // Call USER_GPIO_PushCommand to insert command to pLocalList
    Status status = USER_GPIO_PushCommand(&localCmdBlock);

    LONGS_EQUAL(OK, status);

    // Set command with SWITCH_CHANNEL state
    localCmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
    localCmdBlock.channel = CHANNEL_B;
    localCmdBlock.specificator = NULL;

    // Call USER_GPIO_PushCommand to insert command to pLocalList
    status = USER_GPIO_PushCommand(&localCmdBlock);

    LONGS_EQUAL(OK, status);

    // Act #1
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    // Assert #1
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
    // Check other Emulated GPIOs not changed - in case of EXECUTOR_STATE_SWITCH_CHANNEL, we can't verify GPIOs because of static stateA and stateB
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);


    // Act #2
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    // Assert #2
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
    // Check other Emulated GPIOs not changed - in case of EXECUTOR_STATE_SWITCH_CHANNEL, we can't verify GPIOs because of static stateA and stateB
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);

}

TEST(Executor, ShouldHandleToggleChannelState)
{
    //----------Arrange----------//
    // Set all emulatedGpio to GPIO_PIN_RESET
    memset(&emulatedGpio, GPIO_PIN_RESET, sizeof(EmulatedGpioStatesStruct));

    // Set DISTORTION/FUZZ code for Channel B
    emulatedGpio.codeB0 = GPIO_PIN_RESET;
    emulatedGpio.codeB1 = GPIO_PIN_SET;
    // Set command with SWITCH_CHANNEL state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_TOGGLE_CHANNEL;
    localCmdBlock.channel = CHANNEL_B;
    localCmdBlock.specificator = NULL;

    // Call USER_GPIO_PushCommand to insert command to pLocalList
    Status status = USER_GPIO_PushCommand(&localCmdBlock);

    LONGS_EQUAL(OK, status);

    //----------Act----------//
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    //----------Assert----------//
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);

    // Check Emulated GPIOs changed correctly
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);
}


TEST(Executor, ShouldHandleSwitchChannelState)
{
    //----------Arrange----------//
    // Set all emulatedGpio to GPIO_PIN_RESET
    memset(&emulatedGpio, GPIO_PIN_RESET, sizeof(EmulatedGpioStatesStruct));

    // Set BOOSTER/OVERDRIVE code for Channel A
    emulatedGpio.codeA0 = GPIO_PIN_SET;
    emulatedGpio.codeA1 = GPIO_PIN_SET;

    // Set command with SWITCH_CHANNEL state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
    localCmdBlock.channel = CHANNEL_A;
    localCmdBlock.specificator = NULL;

    // Call USER_GPIO_PushCommand to insert command to pLocalList
    Status status = USER_GPIO_PushCommand(&localCmdBlock);

    LONGS_EQUAL(OK, status);

    //----------Act----------//
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    //----------Assert----------//
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);

    // Check other Emulated GPIOs not changed - in case of EXECUTOR_STATE_SWITCH_CHANNEL, we can't verify GPIOs because of static stateA and stateB
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);
}