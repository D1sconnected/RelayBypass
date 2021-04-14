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


// ќбработка сообщений по UART
// pSelf Ц указатель на объект типа Serial
//
// ¬озвращаемые значени€:
//  OK Ц в случае успешной обработки сообщени€
//  NO_COMMAND Ц при отсутствии известной команды в буфере
Status Serial_Handler(Serial *pSelf);

// ѕроверка наличи€ данных в буфере приема UART
//  pSelf Ц указатель на объект типа Serial
//  pCmd Ц указатель на буфер, в который будут скопированы все прин€тые данные
// 
// ¬озвращаемые значени€:
//  OK Ц в случае наличи€ данных в буфере приема
//  NO_DATA Ц при отсутствии данных в буфере приема
Status Serial_ReceiveCmd(Serial *pSelf, char *pCmd);

// ќтправка данных по UART
//  pSelf Ц указатель на объект типа Serial
//  pRes Ц указатель на данные дл€ отправки
// 
// ¬озвращаемые значени€:
//  OK Ц в случае успешной отправки, иначе Ц FAIL
Status Serial_SendResponse(Serial *pSelf, char *pRes);

// ќчистка буфера приема UART
//  pSelf Ц указатель на объект типа Serial
// ¬озвращаемые значени€:
//  OK Ц в случае успешного выполнени€, иначе Ц FAIL
Status Serial_Clear(Serial *pSelf);

#endif