#include "CppUTest/TestHarness.h"

extern "C"
{
#include "Serial.h"
#include "SerialSpy.h"
#include "InterfaceSpy.h"
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
    char toggleCmd[] = "toggle A\r\n";
    LONGS_EQUAL(OK, SerialSpy_SetRxBuffer(pSerial, toggleCmd, sizeof(toggleCmd)));

    // Act – Call to Handler for command processing
    Status status = Serial_Handler(pSerial);

    // Assert – Check returned status
    LONGS_EQUAL(OK, status);
    // Check response sended from UART to PC
    char* pTxBuffer = NULL;
    LONGS_EQUAL(OK, SerialSpy_GetTxBuffer(pSerial, &pTxBuffer));
    char str[16] = {0};
    strcat_s(str, TOGGLE_OUTPUT);
    strcat_s(str, "A\r\n");
    STRCMP_EQUAL(str, pTxBuffer);
}

TEST(Serial, ShouldHandleSwitchCommand)
{
    // Arrange – set command from PC tu UART Rx Buffer
    char switchCmd[] = "switch B\r\n";
    LONGS_EQUAL(OK, SerialSpy_SetRxBuffer(pSerial, switchCmd, sizeof(switchCmd)));

    // Act – Call to Handler for command processing
    Status status = Serial_Handler(pSerial);

    // Assert – Check returned status
    LONGS_EQUAL(OK, status);
    // Check response sended from UART to PC
    char* pTxBuffer = NULL;
    LONGS_EQUAL(OK, SerialSpy_GetTxBuffer(pSerial, &pTxBuffer));
    char str[16] = { 0 };
    strcat_s(str, SWITCH_OUTPUT);
    strcat_s(str, "B\r\n");
    STRCMP_EQUAL(str, pTxBuffer);
}

TEST(Serial, ShouldHandleGetCommand) 
{
    // Arrange – set command from PC tu UART Rx Buffer
    char getCmd[] = "get A\r\n";
    LONGS_EQUAL(OK, SerialSpy_SetRxBuffer(pSerial, getCmd, sizeof(getCmd)));

    // Act – Call to Handler for command processing
    Status status = Serial_Handler(pSerial);

    // Assert – Check returned status
    LONGS_EQUAL(OK, status);
    // Check response sended from UART to PC
    char* pTxBuffer = NULL;
    LONGS_EQUAL(OK, SerialSpy_GetTxBuffer(pSerial, &pTxBuffer));
    char str[16] = { 0 };
    strcat_s(str, GET_OUTPUT);
    strcat_s(str, "A: ");
    strcat_s(str, "RED\r\n");
    STRCMP_EQUAL(str, pTxBuffer);
}

TEST(Serial, ShouldHandleUnknownCommand)
{
    // Arrange – set command from PC tu UART Rx Buffer
    char unknowCmd[] = "unknown command\r\n";
    LONGS_EQUAL(OK, SerialSpy_SetRxBuffer(pSerial, unknowCmd, sizeof(unknowCmd)));

    // Act – Call to Handler for command processing
    Status status = Serial_Handler(pSerial);

    // Assert – Check returned status
    LONGS_EQUAL(UNSUPPORTED, status);
}

