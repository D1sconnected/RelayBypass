/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../sdcard/sdcard.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void MicroSd_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void MicroSd_Init(void)
{
    int code = 0;
    //UART_Printf("Ready!\r\n");

    do
    {
        code = SDCARD_Init();
    } while (code != 0);
    /*
    code = SDCARD_Init();
    if(code < 0) {
        //UART_Printf("SDCARD_Init() failed: code = %d\r\n", code);
        return;
    }
    */

    //UART_Printf("SDCARD_Init() done!\r\n");

    uint32_t blocksNum;
    code = SDCARD_GetBlocksNumber(&blocksNum);
    if(code < 0) {
        //UART_Printf("SDCARD_GetBlocksNumber() failed: code = %d\r\n", code);
        return;
    }

    //UART_Printf("SDCARD_GetBlocksNumber() done! blocksNum = %u (or %u Mb)\r\n",
        //blocksNum, blocksNum/2000 /* same as * 512 / 1000 / 1000 */);

    uint32_t startBlockAddr = 0x00;
    uint32_t blockAddr = startBlockAddr;
    uint8_t block[512];

    //snprintf((char*)block, sizeof(block), "0x%08X", (int)blockAddr);
    /*
    code = SDCARD_WriteSingleBlock(blockAddr, block);
    if(code < 0) {
        //UART_Printf("SDCARD_WriteSingleBlock() failed: code = %d\r\n", code);
        return;
    }
    //UART_Printf("SDCARD_WriteSingleBlock(0x%08X, ...) done!\r\n", blockAddr);
    */
    memset(block, 0, sizeof(block));

    code = SDCARD_ReadSingleBlock(blockAddr, block);
    if(code < 0) {
        //UART_Printf("SDCARD_ReadSingleBlock() failed: code = %d\r\n", code);
        return;
    }

    //UART_Printf("SDCARD_ReadSingleBlock(0x%08X, ...) done! block = \"%c%c%c%c%c%c%c%c%c%c...\"\r\n",
        //blockAddr, block[0], block[1], block[2], block[3], block[4], block[5], block[6], block[7], block[8], block[9]);

    return;

    blockAddr = startBlockAddr + 1;
    code = SDCARD_WriteBegin(blockAddr);
    if(code < 0) {
        //UART_Printf("SDCARD_WriteBegin() failed: code = %d\r\n", code);
        return;
    }
    //UART_Printf("SDCARD_WriteBegin(0x%08X, ...) done!\r\n", blockAddr);

    for(int i = 0; i < 3; i++) {
        snprintf((char*)block, sizeof(block), "0x%08X", (int)blockAddr);

        code = SDCARD_WriteData(block);
        if(code < 0) {
            //UART_Printf("SDCARD_WriteData() failed: code = %d\r\n", code);
            return;
        }

        //UART_Printf("SDCARD_WriteData() done! blockAddr = %08X\r\n", blockAddr);
        blockAddr++;
    }

    code = SDCARD_WriteEnd();
    if(code < 0) {
        //UART_Printf("SDCARD_WriteEnd() failed: code = %d\r\n", code);
        return;
    }
    //UART_Printf("SDCARD_WriteEnd() done!\r\n");

    blockAddr = startBlockAddr + 1;
    code = SDCARD_ReadBegin(blockAddr);
    if(code < 0) {
        //UART_Printf("SDCARD_ReadBegin() failed: code = %d\r\n", code);
        return;
    }
    //UART_Printf("SDCARD_ReadBegin(0x%08X, ...) done!\r\n", blockAddr);

    for(int i = 0; i < 3; i++) {
        code = SDCARD_ReadData(block);
        if(code < 0) {
            //UART_Printf("SDCARD_ReadData() failed: code = %d\r\n", code);
            return;
        }

        //UART_Printf("SDCARD_ReadData() done! block = \"%c%c%c%c%c%c%c%c%c%c...\"\r\n",
            //block[0], block[1], block[2], block[3], block[4], block[5], block[6], block[7], block[8], block[9]);
    }

    code = SDCARD_ReadEnd();
    if(code < 0) {
        //UART_Printf("SDCARD_ReadEnd() failed: code = %d\r\n", code);
        return;
    }
    //UART_Printf("SDCARD_ReadEnd() done!\r\n");
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  MicroSd_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
