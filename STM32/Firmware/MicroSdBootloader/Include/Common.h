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
    NEED_TO_UPDATE = -10,
} Status;

#endif
