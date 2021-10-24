#include "CppUTest/TestHarness.h"

extern "C"
{

#ifdef STM32F1_VERSION
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/main.h"
#include "stm32f1xx_hal.h"
#include "../../../Firmware/RelayBypass_STM32F101C4/Core/Inc/tim.h"
#endif

#ifdef STM32L1_VERSION
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/main.h"
#include "stm32l1xx_hal.h"
#include "../../../Firmware/RelayBypass_STM32L151C8/Core/Inc/tim.h"
#endif

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
    //----------ARRANGE #1----------//
    memset(&emulatedGpio, GPIO_PIN_RESET, sizeof(EmulatedGpioStatesStruct));
    // Reset Channel A & Channel B to FX_OFF
    gFxStateA = FX_OFF;
    gFxStateB = FX_OFF;
    // Set BOOSTER/OVERDRIVE code for Channel A
    emulatedGpio.codeA0 = GPIO_PIN_SET;
    emulatedGpio.codeA1 = GPIO_PIN_SET;
    // Set BOOSTER/OVERDRIVE code for Channel B
    emulatedGpio.codeB0 = GPIO_PIN_SET;
    emulatedGpio.codeB1 = GPIO_PIN_SET;

    // Call HAL_GPIO_EXTI_Callback
    emulatedGpio.buttonA = GPIO_PIN_RESET;
    emulatedGpio.buttonB = GPIO_PIN_SET;
    HAL_GPIO_EXTI_Callback(A_BTN_Pin);

    // Call HAL_TIM_PeriodElapsedCallback
    HAL_TIM_PeriodElapsedCallback(&htim2);

    //----------ACT #1----------//
    // Call Executor_Handler with pointer to Executor's List
    Status status = Executor_Handler(pExecutor);

    //----------ASSERT #1----------//
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
    // Check Emulated GPIOs changed correctly
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.releA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedA);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.ledGreenA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);

    //----------ARRANGE #2----------//
    // Call HAL_GPIO_EXTI_Callback
    emulatedGpio.buttonA = GPIO_PIN_SET;
    emulatedGpio.buttonB = GPIO_PIN_RESET;
    HAL_GPIO_EXTI_Callback(B_BTN_Pin);

    // Call HAL_TIM_PeriodElapsedCallback
    HAL_TIM_PeriodElapsedCallback(&htim2);

    //----------ACT #2----------//
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    //----------ASSERT #2----------//
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
    // Check Emulated GPIOs changed correctly
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.releA);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.releB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedA);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.ledGreenA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);
}

TEST(Executor, ShouldHandleSwitchChannelFromButtonB)
{
    //----------ARRANGE----------//
    memset(&emulatedGpio, GPIO_PIN_RESET, sizeof(EmulatedGpioStatesStruct));
    // Reset Channel A & Channel B to FX_OFF
    gFxStateA = FX_OFF;
    gFxStateB = FX_OFF;
    // Set BOOSTER/OVERDRIVE code for Channel B
    emulatedGpio.codeB0 = GPIO_PIN_SET;
    emulatedGpio.codeB1 = GPIO_PIN_SET;

    // Call HAL_GPIO_EXTI_Callback
    emulatedGpio.buttonA = GPIO_PIN_SET;
    emulatedGpio.buttonB = GPIO_PIN_RESET;
    HAL_GPIO_EXTI_Callback(B_BTN_Pin);

    // Call HAL_TIM_PeriodElapsedCallback
    HAL_TIM_PeriodElapsedCallback(&htim2);

    //----------ACT----------//
    // Call Executor_Handler with pointer to Executor's List
    Status status = Executor_Handler(pExecutor);

    //----------ASSERT----------//
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
    // Check Emulated GPIOs changed correctly
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releA);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.releB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);
}

TEST(Executor, ShouldHandleSwitchChannelFromButtonA)
{
    //----------ARRANGE----------//
    memset(&emulatedGpio, GPIO_PIN_RESET, sizeof(EmulatedGpioStatesStruct));
    // Reset Channel A & Channel B to FX_OFF
    gFxStateA = FX_OFF;
    gFxStateB = FX_OFF;
    // Set OTHER code for Channel A
    emulatedGpio.codeA0 = GPIO_PIN_SET;
    emulatedGpio.codeA1 = GPIO_PIN_RESET;

    // Call HAL_GPIO_EXTI_Callback
    emulatedGpio.buttonA = GPIO_PIN_RESET;
    emulatedGpio.buttonB = GPIO_PIN_SET;
    HAL_GPIO_EXTI_Callback(A_BTN_Pin);

    // Call HAL_TIM_PeriodElapsedCallback
    HAL_TIM_PeriodElapsedCallback(&htim2);

    //----------ACT----------//
    // Call Executor_Handler with pointer to Executor's List
    Status status = Executor_Handler(pExecutor);

    //----------ASSERT----------//
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
    // Check Emulated GPIOs changed correctly
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.releA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenA);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);
}

TEST(Executor, ShouldHandleChangeRouteState)
{
    //----------ARRANGE----------//
    memset(&emulatedGpio, GPIO_PIN_RESET, sizeof(EmulatedGpioStatesStruct));
    // Set command with SWITCH_CHANNEL state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_CHANGE_ROUTE;
    localCmdBlock.channel = CHANNEL_B;
    localCmdBlock.specificator = NULL;

    // Call USER_GPIO_PushCommand to insert command to pGpioList
    Status status = Button_PushCommand(&localCmdBlock);
    LONGS_EQUAL(OK, status);

    //----------ACT----------//
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    //----------ASSERT----------//
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
    // Check Emulated GPIOs changed correctly
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releB);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);
}

TEST(Executor, ShouldHandleSequenceOfStates)
{
    //----------ARRANGE----------//
    memset(&emulatedGpio, GPIO_PIN_RESET, sizeof(EmulatedGpioStatesStruct));
    // Reset Channel A & Channel B to FX_OFF
    gFxStateA = FX_OFF;
    gFxStateB = FX_OFF;
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

    // Call USER_GPIO_PushCommand to insert command to pGpioList
    Status status = Button_PushCommand(&localCmdBlock);
    LONGS_EQUAL(OK, status);

    // Set command with SWITCH_CHANNEL state
    localCmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
    localCmdBlock.channel = CHANNEL_B;
    localCmdBlock.specificator = NULL;

    // Call USER_GPIO_PushCommand to insert command to pGpioList
    status = Button_PushCommand(&localCmdBlock);
    LONGS_EQUAL(OK, status);

    //----------ACT #1----------//
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    //----------ASSERT #1----------//
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
    // Check Emulated GPIOs changed correctly
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.releA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.ledRedA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);

    //----------ACT #2----------//
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    //----------ASSERT #2----------//
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);
    // Check Emulated GPIOs changed correctly
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.releA);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.releB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.ledRedA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.ledBlueB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);

}

TEST(Executor, ShouldHandleToggleChannelState)
{
    //----------ARRANGE----------//
    memset(&emulatedGpio, GPIO_PIN_RESET, sizeof(EmulatedGpioStatesStruct));

    // Set DISTORTION/FUZZ code for Channel B
    emulatedGpio.codeB0 = GPIO_PIN_RESET;
    emulatedGpio.codeB1 = GPIO_PIN_SET;
    // Set command with SWITCH_CHANNEL state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_TOGGLE_CHANNEL;
    localCmdBlock.channel = CHANNEL_B;
    localCmdBlock.specificator = NULL;

    // Call USER_GPIO_PushCommand to insert command to pGpioList
    Status status = Button_PushCommand(&localCmdBlock);
    LONGS_EQUAL(OK, status);

    //----------ACT----------//
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    //----------ASSERT----------//
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
    //----------ARRANGE----------//
    memset(&emulatedGpio, GPIO_PIN_RESET, sizeof(EmulatedGpioStatesStruct));
    // Reset Channel A to FX_OFF
    gFxStateA = FX_OFF;

    // Set BOOSTER/OVERDRIVE code for Channel A
    emulatedGpio.codeA0 = GPIO_PIN_SET;
    emulatedGpio.codeA1 = GPIO_PIN_SET;

    // Set command with SWITCH_CHANNEL state
    StateStruct localCmdBlock;
    localCmdBlock.state = EXECUTOR_STATE_SWITCH_CHANNEL;
    localCmdBlock.channel = CHANNEL_A;
    localCmdBlock.specificator = NULL;

    // Call USER_GPIO_PushCommand to insert command to pGpioList
    Status status = Button_PushCommand(&localCmdBlock);
    LONGS_EQUAL(OK, status);

    //----------ACT----------//
    // Call Executor_Handler with pointer to Executor's List
    status = Executor_Handler(pExecutor);

    //----------ASSERT----------//
    // Check FSM returned OK status
    LONGS_EQUAL(OK, status);

    // Check Emulated GPIOs changed correctly
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.releA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir0);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.releDir1);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedA);
    LONGS_EQUAL(GPIO_PIN_SET,   emulatedGpio.ledGreenA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueA);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledRedB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledGreenB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.ledBlueB);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.phet);
    LONGS_EQUAL(GPIO_PIN_RESET, emulatedGpio.mcuProg);
}