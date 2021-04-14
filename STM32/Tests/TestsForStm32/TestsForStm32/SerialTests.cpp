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
    // Arrange Ц установка вход€щей команды от ѕ  в буфер приема UART
    char helpCmd[] = "help\r\n";
    LONGS_EQUAL(OK, SerialSpy_SetRxBuffer(pSerial, helpCmd, sizeof(helpCmd)));

    // Act Ц вызов обработчика команд
    Status status = Serial_Handler(pSerial);

    // Assert Ц проверка статуса обработки
    LONGS_EQUAL(OK, status);
    // проверка ответа, отправленного обратно на ѕ  по UART
    char* pTxBuffer = NULL;
    LONGS_EQUAL(OK, SerialSpy_GetTxBuffer(pSerial, &pTxBuffer));
    STRCMP_EQUAL(HELP_OUTPUT, pTxBuffer);
}