// Loader.h
#ifndef LOADER_HEADER_FILE_H
#define LOADER_HEADER_FILE_H

#include "Common.h"

typedef uint8_t Loader;

Loader * Loader_Create(void);
void Loader_Destroy(Loader* pSelf);

#endif