/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "defines.h"
#include "serial.h"
#include "gpios.h"

#include "config.h"

//#include "Model/Button.h"

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
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
#define MAXCLISTRING 200
uint8_t rxBuffer; // where we store that one character that just came in
uint8_t rxString[MAXCLISTRING], rxLastString[MAXCLISTRING]; // where we build our string from characters coming in
int rxindex = 0; // index for going though rxString

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

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
//	Model::Button button(GPIOA, GPIO_PIN_7);

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
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  PR_GPIOs_Init();

  print("\n\r# > ");
  __HAL_UART_FLUSH_DRREGISTER(&huart3);
  HAL_UART_Receive_IT(&huart3, &rxBuffer, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(huart3.RxXferCount == 0)
	  {
		  tolog(".");
		  // HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_2);
		  HAL_UART_Receive_IT(&huart3, &rxBuffer, 1);
	  }
//	  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_2, HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2));
//	  HAL_Delay(500);
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
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin : PE2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  //HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	__HAL_UART_FLUSH_DRREGISTER(&huart3); // Clear the buffer to prevent overrun

	int i = 0;

	if (rxBuffer == '\003'){ // Ctrl+C
		SR_setSerialStatus(UART_STATUS_INPUT);
		rxindex = 0;
		for (i = 0; i < MAXCLISTRING; i++) rxString[i] = 0; // Clear the string buffer
		print("\n\r# > ");
	} else if (SR_getSerialStatus() == UART_STATUS_LOGS) {
		// do nothing
	} else if (rxBuffer == '\e') { // Waiting an arrow
		SR_setSerialStatus(UART_STATUS_ARROW);
	} else if (SR_getSerialStatus() == UART_STATUS_ARROW) {
		if (rxBuffer != '[') {
			switch (rxBuffer) {
				case 'A':
					for (; rxindex > 0; rxindex--) {
						print("\b \b");
					}
					// code for arrow up
					memcpy(rxString, rxLastString, MAXCLISTRING);
					rxindex = strlen(rxString);
					print(rxString);
					break;
				case 'B':
					// code for arrow down
					break;
				case 'C':
					// code for arrow right
					break;
				case 'D':
					// code for arrow left
					break;
			}
			SR_setSerialStatus(UART_STATUS_INPUT);
		}
	} else if (rxBuffer == 8 || rxBuffer == 127) { // If Backspace or del
		rxindex--;
		if (rxindex < 0) {
			rxindex = 0;
		} else {
			print("\b \b"); // "\b space \b" clears the terminal character. Remember we just echoced a \b so don't need another one here, just space and \b
		}
		rxString[rxindex] = 0;
	} else if (rxBuffer == '\n' || rxBuffer == '\r') { // If Enter
		print("\n\r");
		memcpy(rxLastString, rxString, MAXCLISTRING);

		SR_execCommand(rxString);

		for (int i = 0; i < MAXCLISTRING; i++) {
			rxString[i] = 0; // Clear the string buffer
		}

		rxString[rxindex] = 0;
		rxindex = 0;

		if (SR_getSerialStatus() != UART_STATUS_LOGS) {
			print("\n\r# > ");
		}

	} else if (isprint(rxBuffer)){
		print(&rxBuffer); // Echo the character that caused this callback so the user can see what they are typing

		rxString[rxindex] = rxBuffer; // Add that character to the string
		rxindex++;
		if (rxindex > MAXCLISTRING) { // User typing too much, we can't have commands that big
			rxindex = 0;
			for (i = 0; i < MAXCLISTRING; i++) rxString[i] = 0; // Clear the string buffer
			print("\n\r# > ");
		}
	}
}

void print(char *str)
{
	HAL_UART_Transmit(&huart3, (uint8_t*)str, strlen(str), 0xFFFF);
}

void tolog(char *str)
{
	if (SR_getSerialStatus() == UART_STATUS_LOGS) {
		print(str);
	}
}

char *getFwVersion()
{
	return FW_VERSION;
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
     tex: printf("Wrong parameters value: file %s on line %d\n\r", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
