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
    // Arrange � ��������� �������� ������� �� �� � ����� ������ UART
    char helpCmd[] = "help\r\n";
    LONGS_EQUAL(OK, SerialSpy_SetRxBuffer(pSerial, helpCmd, sizeof(helpCmd)));

    // Act � ����� ����������� ������
    Status status = Serial_Handler(pSerial);

    // Assert � �������� ������� ���������
    LONGS_EQUAL(OK, status);
    // �������� ������, ������������� ������� �� �� �� UART
    char* pTxBuffer = NULL;
    LONGS_EQUAL(OK, SerialSpy_GetTxBuffer(pSerial, &pTxBuffer));
    STRCMP_EQUAL(HELP_OUTPUT, pTxBuffer);
}