// Flash.h
#ifndef FLASH_HEADER_FILE_H
#define FLASH_HEADER_FILE_H

#include "Common.h"
#include "../Core/Inc/main.h"
#include "./../../SharedLibs/sdcard/sdcard.h"

#define FLASH_USER_START_ADDR       0x08001800
#define SECTOR_SIZE_IN_BYTES        512
#define PAGE_SIZE_IN_BYTES          1024
#define MAX_FW_SIZE_IN_PAGES        10
#define MAX_FW_SIZE_IN_SECTORS      2 * MAX_FW_SIZE_IN_PAGES
#define MAX_FW_SIZE_IN_BYTES        MAX_FW_SIZE_IN_SECTORS * SECTOR_SIZE_IN_BYTES

Status Flash_Init(void);
Status Flash_DeInit(void);
Status Flash_Erase(uint8_t pageNumber);
Status Flash_Read(uint32_t offset, uint32_t *pData);
Status Flash_Write(uint32_t address, uint32_t data);

#endif