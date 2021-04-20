// Common.h
#ifndef COMMON_HEADER_FILE_H
#define COMMON_HEADER_FILE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    OK = 0,
    FAIL = -1,
    INVALID_PARAMETERS = -3,
    OUT_OF_BOUNDS = -4,
    UNSUPPORTED = -5,
    NO_DATA = -6,
    NO_COMMAND = -7,
    INVALID_FORMAT = -8,
	NO_NEW_COMMANDS = -9,
} Status;

typedef enum
{
	EXECUTOR_STATE_UPDATE_LIST,
	EXECUTOR_STATE_GET_CMD,
	EXECUTOR_STATE_SWITCH_CHANNEL,
	EXECUTOR_STATE_CHANGE_ROUTE,
	EXECUTOR_STATE_SAVE_ROUTE,
	EXECUTOR_STATE_TOGGLE_CHANNEL,
	EXECUTOR_STATE_GET_CHANNEL,
	EXECUTOR_STATE_TRACE_TO_MICROSD,
	EXECUTOR_STATE_TRACE_TO_UART,
	EXECUTOR_STATE_GET_UART_RX,
	EXECUTOR_STATE_SEND_UART_TX,
	EXECUTOR_STATE_WRITE_TO_DISPLAY,
	EXECUTOR_STATE_CONFIG_EXT_CTRL_TIM
} ExecutorState;

#endif