#include "gpios.h"

GPIO_TypeDef *PR_Init_CLK(t_GPIO_TYPE type);
GPIO_TypeDef *PR_GetGPIOx_byType(t_GPIO_TYPE type);

void PR_GPIOs_Init()
{
	#include "config.h"

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	int len = (sizeof(a_GPIOS) / sizeof(t_GPIO));
	GPIO_TypeDef *GPIOx;

	uint32_t tmp;
	for (int i = 0; i < len; i++) {
		GPIOx = PR_Init_CLK(a_GPIOS[i].type);
		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOx, a_GPIOS[i].pin, GPIO_PIN_RESET);

		GPIO_InitStruct.Pin = a_GPIOS[i].pin;
		GPIO_InitStruct.Pin = GPIO_PIN_4;
		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;// 01
//		GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // 00
//		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; // 11
//		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // 10

		HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
	}
}

GPIO_TypeDef *PR_Init_CLK(t_GPIO_TYPE type)
{
	switch (type) {
		case TYPE_GPIOA:
			__HAL_RCC_GPIOA_CLK_ENABLE();
			break;
		case TYPE_GPIOB:
			__HAL_RCC_GPIOB_CLK_ENABLE();
			break;
		case TYPE_GPIOC:
			__HAL_RCC_GPIOC_CLK_ENABLE();
			break;
		case TYPE_GPIOD:
			__HAL_RCC_GPIOD_CLK_ENABLE();
			break;
		case TYPE_GPIOE:
			__HAL_RCC_GPIOE_CLK_ENABLE();
			break;
		case TYPE_GPIOF:
			__HAL_RCC_GPIOF_CLK_ENABLE();
			break;
		case TYPE_GPIOG:
			__HAL_RCC_GPIOG_CLK_ENABLE();
			break;
		case TYPE_GPIOH:
			__HAL_RCC_GPIOH_CLK_ENABLE();
			break;
		case TYPE_GPIOI:
			__HAL_RCC_GPIOI_CLK_ENABLE();
			break;
		default:
			break;
	}

	return PR_GetGPIOx_byType(type);
}


GPIO_TypeDef *PR_GetGPIOx_byType(t_GPIO_TYPE type)
{
	switch (type) {
		case TYPE_GPIOA:
			return GPIOA;
			break;
		case TYPE_GPIOB:
			return GPIOB;
			break;
		case TYPE_GPIOC:
			return GPIOC;
			break;
		case TYPE_GPIOD:
			return GPIOD;
			break;
		case TYPE_GPIOE:
			return GPIOE;
			break;
		case TYPE_GPIOF:
			return GPIOF;
			break;
		case TYPE_GPIOG:
			return GPIOG;
			break;
		case TYPE_GPIOH:
			return GPIOH;
			break;
		case TYPE_GPIOI:
			return GPIOI;
			break;
		default:
			break;
	}

	return NULL;
}

t_GPIO_MODE *PR_getGPIOmode(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	int n = 0;
	while ((GPIO_Pin >> ++n) != 0); // Find the bit position

	int type = (GPIOx->MODER >> (n-1)*2) & 3U;
	switch (type) {
		case 0U:
			return PR_GPIO_MODE_INPUT;
			break;
		case 1U:
			return PR_GPIO_MODE_OUTPUT;
			break;
		case 2U:
			return PR_GPIO_MODE_ALTERNATIVE;
			break;
		case 3U:
			return PR_GPIO_MODE_ANALOG;
			break;
		default:
			return NULL;
	}
}
