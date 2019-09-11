#include "gpios.h"


GPIO_TypeDef *PR_Init_CLK(t_GPIO_TYPE type);
GPIO_TypeDef *PR_GetGPIOx_byType(t_GPIO_TYPE type);
TM_GPIO_Mode_t PR_getGPIOmode(GPIO_TypeDef* GPIOx, uint16_t pin);
extern t_GPIO *a_GPIOS;
extern uint16_t GPIOS_COUNT;

void PR_GPIOs_Init()
{
	for (int i = 0; i < GPIOS_COUNT; i++) {
		PR_GPIO_SetMode(&a_GPIOS[i], TM_GPIO_Mode_IN);
	}
}

void PR_GPIO_SetMode(t_GPIO *gpio, TM_GPIO_Mode_t mode)
{
	uint16_t GPIO_Pin = 1 << gpio->pin;
	GPIO_TypeDef *GPIOx = PR_Init_CLK(gpio->type);
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;// 01
	//	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // 00
	//	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; // 11
	//	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // 10

	switch (mode) {
		case TM_GPIO_Mode_IN:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // 00
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;
		case TM_GPIO_Mode_OUT:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;// 01
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			break;
		default:
			return;
			break;
	}

	GPIO_InitStruct.Pin = GPIO_Pin;

	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

GPIO_TypeDef *PR_Init_CLK(t_GPIO_TYPE type)
{
	switch (type) {
		case TYPE_GPIOA:
			if (__HAL_RCC_GPIOA_IS_CLK_DISABLED()) {
				__HAL_RCC_GPIOA_CLK_ENABLE();
			}
			break;
		case TYPE_GPIOB:
			if (__HAL_RCC_GPIOB_IS_CLK_DISABLED()) {
				__HAL_RCC_GPIOB_CLK_ENABLE();
			}
			break;
		case TYPE_GPIOC:
			if (__HAL_RCC_GPIOC_IS_CLK_DISABLED()) {
				__HAL_RCC_GPIOC_CLK_ENABLE();
			}
			break;
		case TYPE_GPIOD:
			if (__HAL_RCC_GPIOD_IS_CLK_DISABLED()) {
				__HAL_RCC_GPIOD_CLK_ENABLE();
			}
			break;
		case TYPE_GPIOE:
			if (__HAL_RCC_GPIOE_IS_CLK_DISABLED()) {
				__HAL_RCC_GPIOE_CLK_ENABLE();
			}
			break;
		case TYPE_GPIOF:
			if (__HAL_RCC_GPIOF_IS_CLK_DISABLED()) {
				__HAL_RCC_GPIOF_CLK_ENABLE();
			}
			break;
		case TYPE_GPIOG:
			if (__HAL_RCC_GPIOG_IS_CLK_DISABLED()) {
				__HAL_RCC_GPIOG_CLK_ENABLE();
			}
			break;
		case TYPE_GPIOH:
			if (__HAL_RCC_GPIOH_IS_CLK_DISABLED()) {
				__HAL_RCC_GPIOH_CLK_ENABLE();
			}
			break;
		case TYPE_GPIOI:
			if (__HAL_RCC_GPIOI_IS_CLK_DISABLED()) {
				__HAL_RCC_GPIOI_CLK_ENABLE();
			}
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

TM_GPIO_Mode_t PR_getGPIOmode(GPIO_TypeDef* GPIOx, uint16_t pin)
{
	// for GPIO struct
	//int n = 0;
	//while ((GPIO_Pin >> ++n) != 0); // Find the bit position
	//int type = (GPIOx->MODER >> (n-1)*2) & 3U;

	int type = (GPIOx->MODER >> (pin*2) & 3U);

	return type;
}

GPIO_PinState PR_getGPIOvalue(GPIO_TypeDef* GPIOx, uint16_t pin)
{
	TM_GPIO_Mode_t mode = PR_getGPIOmode(GPIOx, pin);
	uint16_t GPIO_Pin = 1 << pin;
	switch (mode) {
		case TM_GPIO_Mode_IN:
			return HAL_GPIO_ReadPin(GPIOx, 1 << pin);
			break;
		case TM_GPIO_Mode_OUT:
			return ((GPIOx->ODR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)? GPIO_PIN_SET: GPIO_PIN_RESET;
			break;
		defualt:
			break;
	}

	return HAL_GPIO_ReadPin(GPIOx, 1 << pin);
}
