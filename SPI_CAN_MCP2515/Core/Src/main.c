/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "CANSPI.h"
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
uint32_t cnt = 0;
uCAN_MSG txMessage;
uCAN_MSG rxMessage;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */



/* We need to implement own __FILE struct */
/* FILE struct is used from __FILE */
struct __FILE {
    int dummy;
};
 
/* You need this if you want use printf */
/* Struct FILE is implemented in stdio.h */
FILE __stdout;


int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF); 

  return ch;
}



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_SPI2_Init();
  MX_TIM3_Init();
  MX_TIM7_Init();
  MX_DMA_Init();
  MX_USART3_UART_Init();
  MX_TIM4_Init();
  MX_SPI3_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	CANSPI_Initialize(OSC_8MHZ, 500);	// OSC, kbps
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	txMessage.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
	txMessage.frame.id = 0x00A;
	txMessage.frame.dlc = 8;
	txMessage.frame.data0 = 0;
	txMessage.frame.data1 = 1;
	txMessage.frame.data2 = 2;
	txMessage.frame.data3 = 3;
	txMessage.frame.data4 = 4;
	txMessage.frame.data5 = 5;
	txMessage.frame.data6 = 6;
	txMessage.frame.data7 = 8;
	
	
	
	// M0 -> F0, F1
	// M1 -> F2, F3, F4, F5
	//CANSPI_SetFilterMask(0, 0x7E7, 0, 0x1EF);
	CANSPI_SetFilterMask(0, 0, 0, 0);
	
  while (1)
  {
		if(CANSPI_Receive(&rxMessage))
		{
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			printf("%s\r\n", "Message Arrived");
			//sprintf();
			
			
			printf("%d\r\n", rxMessage.frame.idType);
			printf("%x\r\n", rxMessage.frame.idType);
			printf("%u\r\n", rxMessage.frame.id);
			printf("%x\r\n", rxMessage.frame.id);
			printf("0x%02x\r\n", rxMessage.frame.data0);
			printf("0x%02x\r\n", rxMessage.frame.data1);
			printf("0x%02x\r\n", rxMessage.frame.data2);
			printf("0x%02x\r\n", rxMessage.frame.data3);
			printf("0x%02x\r\n", rxMessage.frame.data4);
			printf("0x%02x\r\n", rxMessage.frame.data5);
			printf("0x%02x\r\n", rxMessage.frame.data6);
			printf("0x%02x\r\n", rxMessage.frame.data7);
			
			printf("==========================\r\n");
			if(rxMessage.frame.idType == (uint8_t)dSTANDARD_CAN_MSG_ID_2_0B)
				printf("ID Type : standard\r\n");
			else if(rxMessage.frame.idType == (uint8_t)dEXTENDED_CAN_MSG_ID_2_0B)
				printf("ID Type : extended\r\n");
			
			printf("ID  : %x\r\n", rxMessage.frame.id);
			printf("DLC : %d\r\n", rxMessage.frame.dlc);
			
			for(int i =0; i < sizeof(rxMessage.dataArray); i++)
			{
				printf("Data-%d : 0x%02x\r\n", i, rxMessage.dataArray[i]);
			}
			printf("==========================\r\n");
			
		}
		//printf("hello\r\n");
		HAL_Delay(1000);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	for(int i =0; i < sizeof(rxMessage.array); i++)
	{
		printf("0x%u\r\n", rxMessage.array[i]);
	}
	//uint8_t tempBuffer[100];
	//int result = 0;
	//result = sprintf((char*)tempBuffer, "%u\r\n", rxMessage.frame.idType);
	//result += sprintf((char*)tempBuffer - sizeof(rxMessage.frame.idType), "%u\r\n", rxMessage.frame.idType);
	//if(result > 0) printf("%s\r\n", tempBuffer);
	//else printf("SPI receive error\r\n");
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static uint32_t temp = 0;
	if(GPIO_Pin == GPIO_PIN_10)
	{
		if(HAL_GetTick() - temp > 100){
			printf("%s\r\n", "PIN_10 Pressed");
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
			txMessage.frame.data7 = 8 + cnt;
			cnt++;
			
			CANSPI_Transmit(&txMessage);
		}
		while(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10) == GPIO_PIN_RESET)
		{
		
		}
		temp = HAL_GetTick();
	}
}
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

