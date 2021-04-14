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
    - toogle: <slot> <count>\r\n"

typedef struct SerialStruct Serial;

Serial *Serial_Create(void);
void Serial_Destroy(Serial *pSelf);


// ��������� ��������� �� UART
// pSelf � ��������� �� ������ ���� Serial
//
// ������������ ��������:
//  OK � � ������ �������� ��������� ���������
//  NO_COMMAND � ��� ���������� ��������� ������� � ������
Status Serial_Handler(Serial *pSelf);

// �������� ������� ������ � ������ ������ UART
//  pSelf � ��������� �� ������ ���� Serial
//  pCmd � ��������� �� �����, � ������� ����� ����������� ��� �������� ������
// 
// ������������ ��������:
//  OK � � ������ ������� ������ � ������ ������
//  NO_DATA � ��� ���������� ������ � ������ ������
Status Serial_ReceiveCmd(Serial *pSelf, char *pCmd);

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