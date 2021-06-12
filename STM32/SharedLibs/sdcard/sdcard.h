/*
MIT License

Copyright (c) 2018 Aleksander Alekseev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* vim: set ai et ts=4 sw=4: */
#ifndef __SDCARD_H__
#define __SDCARD_H__

#include "main.h"

extern SPI_HandleTypeDef hspi1;

#define SDCARD_SPI_PORT      hspi1
#define SDCARD_CS_Pin        SPI1_CS2_Pin
#define SDCARD_CS_GPIO_Port  SPI1_CS2_GPIO_Port

typedef enum
{
    SDCARD_OK                           = 0,
    SDCARD_INIT_FAILED                  = 1,
    SDCARD_GETBLOCKS_NUMBER_FAILED      = 2,
    SDCARD_READ_SINGLE_BLOCK_FAILED     = 3,
    SDCARD_WRITE_SINGLE_BLOCK_FAILED    = 4,
    SDCARD_READ_BEGIN_FAILED            = 5,
    SDCARD_READ_DATA_FAILED             = 6,
    SDCARD_READ_END_FAILED              = 7,
    SDCARD_WRITE_BEGIN_FAILED           = 8,
    SDCARD_WRITE_DATA_FAILED            = 9,
    SDCARD_WRITE_END_FAILED             = 10
} SdCardStatus;

// call before initializing any SPI devices
void SDCARD_Unselect();

// all procedures return 0 on success, < 0 on failure

int SDCARD_Init();
int SDCARD_GetBlocksNumber(uint32_t* num);
int SDCARD_ReadSingleBlock(uint32_t blockNum, uint8_t* buff); // sizeof(buff) == 512!
int SDCARD_WriteSingleBlock(uint32_t blockNum, const uint8_t* buff); // sizeof(buff) == 512!

// Read Multiple Blocks
int SDCARD_ReadBegin(uint32_t blockNum);
int SDCARD_ReadData(uint8_t* buff); // sizeof(buff) == 512!
int SDCARD_ReadEnd();

// Write Multiple Blocks
int SDCARD_WriteBegin(uint32_t blockNum);
int SDCARD_WriteData(const uint8_t* buff); // sizeof(buff) == 512!
int SDCARD_WriteEnd();

// TODO: read lock flag? CMD13, SEND_STATUS

#endif // __SDCARD_H__
