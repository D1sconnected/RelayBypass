// Serial.h
#ifndef SERIAL_HEADER_FILE_H
#define SERIAL_HEADER_FILE_H

#include "Common.h"

#define SERIAL_RX_BUFFER_SIZE	32
#define SERIAL_TX_BUFFER_SIZE	256

#define HELP_OUTPUT \
"Command list:\r\n \
    - help\r\n \
    - get: <slot>\r\n \
    - enable: <slot>\r\n \
    - toogle: <slot>\r\n"

#define TOGGLE_OUTPUT \
"Toggle Slot "

typedef struct SerialStruct Serial;

Serial *Serial_Create(void);
void Serial_Destroy(Serial *pSelf);


// UART message handler
// pSelf � pointer to object with Serial type
//
// Returns:
// OK � in case of success
// NO_COMMAND � in case of unkown command in rxBuffer 
Status Serial_Handler(Serial *pSelf);

// Handler for <help> command
// pSelf � pointer to object with Serial type
//
// Returns:
//  OK � in case of success
//  OUT_OF_BOUNDS - in case of response len > txBuffer
Status Serial_HandleHelpCommand(Serial* pSelf);

// Handler for <toogle> command
// pSelf � pointer to object with Serial type
//
// Returns:
//  OK � in case of success
//  OUT_OF_BOUNDS - in case of response len > txBuffer
Status Serial_HandleToggleCommand(Serial* pSelf);

// �������� ������� ������ � ������ ������ UART
//  pSelf � ��������� �� ������ ���� Serial
// 
// ������������ ��������:
//  OK � � ������ ������� ������ � ������ ������
//  NO_DATA � ��� ���������� ������ � ������ ������
Status Serial_ReceiveCmd(Serial *pSelf);

// �������� ������ �� UART
//  pSelf � ��������� �� ������ ���� Serial
//  pRes � ��������� �� ������ ��� ��������
// 
// ������������ ��������:
//  OK � � ������ �������� ��������, ����� � FAIL
Status Serial_SendResponse(Serial *pSelf, char *pRes);

// ������� ������ ������ UART
//  pSelf � ��������� �� ������ ���� Serial
// ������������ ��������:
//  OK � � ������ ��������� ����������, ����� � FAIL
Status Serial_Clear(Serial *pSelf);

#endif