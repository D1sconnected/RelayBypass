#include "CppUTest/TestHarness.h"

extern "C"
{
#include "SerialCommunicator.h"
#include "SerialSpy.h"
}

TEST_GROUP(SerialCommunicator)
{
    SerialCommunicator *pCommunicator = NULL;
    Serial* pSerial = NULL;

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

TEST(SerialCommunicator, ShouldHandleHelpCommand)
{
    // Arrange � ��������� �������� ������� �� �� � ����� ������ UART
    char helpCmd[] = "help\r\n";
    LONGS_EQUAL(OK, SerialSpy_SetRxBuffer(pSerial, helpCmd, sizeof(helpCmd)));

    // Act � ����� ����������� ������
    Status status = SerialCommunicator_Handler(pCommunicator);

    // Assert � �������� ������� ���������
    LONGS_EQUAL(OK, status);
    // �������� ������, ������������� ������� �� �� �� UART
    char* pTxBuffer = NULL;
    LONGS_EQUAL(OK, SerialSpy_GetTxBuffer(pSerial, &pTxBuffer));
    STRCMP_EQUAL(HELP_OUTPUT, pTxBuffer);
}