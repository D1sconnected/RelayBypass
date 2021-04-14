#include "CppUTest/TestHarness.h"

extern "C"
{
#include "Serial.h"
#include "SerialSpy.h"
}

TEST_GROUP(Serial)
{
    Serial* pSerial = NULL;

    void setup()
    {
        pSerial = Serial_Create();
    }
    void teardown()
    {
        Serial_Destroy(pSerial);
    }
};

TEST(Serial, ShouldNotBeNull)
{
    CHECK_TRUE(pSerial);
}

TEST(Serial, ShouldHandleHelpCommand)
{
    // Arrange – set command from PC tu UART Rx Buffer
    char helpCmd[] = "help\r\n";
    LONGS_EQUAL(OK, SerialSpy_SetRxBuffer(pSerial, helpCmd, sizeof(helpCmd)));

    // Act – Call to Handler for command processing
    Status status = Serial_Handler(pSerial);

    // Assert – Check returned status
    LONGS_EQUAL(OK, status);
    // Check response sended from UART to PC
    char* pTxBuffer = NULL;
    LONGS_EQUAL(OK, SerialSpy_GetTxBuffer(pSerial, &pTxBuffer));
    STRCMP_EQUAL(HELP_OUTPUT, pTxBuffer);
}

TEST(Serial, ShouldHandleToogleCommand)
{
    // Arrange – set command from PC tu UART Rx Buffer
    char toggleCmd[] = "toggle\r\n";
    LONGS_EQUAL(OK, SerialSpy_SetRxBuffer(pSerial, toggleCmd, sizeof(toggleCmd)));

    // Act – Call to Handler for command processing
    Status status = Serial_Handler(pSerial);

    // Assert – Check returned status
    LONGS_EQUAL(OK, status);
    // Check response sended from UART to PC
    char* pTxBuffer = NULL;
    LONGS_EQUAL(OK, SerialSpy_GetTxBuffer(pSerial, &pTxBuffer));
    //STRCMP_EQUAL(HELP_OUTPUT, pTxBuffer);
}