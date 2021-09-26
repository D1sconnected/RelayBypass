// Flash.h
#ifndef FLASH_HEADER_FILE_H
#define FLASH_HEADER_FILE_H

#include "Common.h"
#include "../Core/Inc/main.h"
#include "./../../../SharedLibs/sdcard/sdcard.h"

// With Optimization By Size - 6kB
#define FLASH_USER_START_ADDR           0x08001800

// No Optimization By Size - 10kB
//#define FLASH_USER_START_ADDR           0x08002800

#define FLASH_START_ADDR                0x08000000

#define FLASH_TOTAL_SIZE_IN_BYTES       16384
#define FLASH_BOOTLOADER_SIZE_IN_BYTES  (FLASH_USER_START_ADDR - FLASH_START_ADDR)
#define FLASH_USER_APP_SIZE_IN_BYTES    (FLASH_TOTAL_SIZE_IN_BYTES - FLASH_BOOTLOADER_SIZE_IN_BYTES)

#define PAGE_SIZE_IN_BYTES              1024
#define PAGE_SIZE_IN_DWORDS             256
#define SECTOR_SIZE_IN_BYTES            512
#define SECTOR_SIZE_IN_DWORDS           128

//ToDo Rename FW to USER_APP
#define MAX_FW_SIZE_IN_PAGES            FLASH_USER_APP_SIZE_IN_BYTES / PAGE_SIZE_IN_BYTES
#define MAX_FW_SIZE_IN_SECTORS          2 * MAX_FW_SIZE_IN_PAGES
#define MAX_FW_SIZE_IN_BYTES            MAX_FW_SIZE_IN_SECTORS * SECTOR_SIZE_IN_BYTES
#define MAX_FW_SIZE_IN_DWORDS           MAX_FW_SIZE_IN_BYTES / 4

typedef enum
{
    FLASH_OK            = 0,
    FLASH_INIT_FAILED   = 4,
    FLASH_DEINIT_FAILED = 5,
    FLASH_ERASE_FAILED  = 6,
    FLASH_READ_FAILED   = 7,
    FLASH_WRITE_FAILED  = 8
} FlashStatus;

int Flash_Init(void);
int Flash_DeInit(void);
int Flash_Erase(uint8_t pageNumber);
int Flash_Read(uint32_t offset, uint32_t *pData);
int Flash_Write(uint32_t offset, uint32_t data);

#endif
