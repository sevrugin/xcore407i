#ifndef __GPIOS_H
#define __GPIOS_H

#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_gpio.h"

typedef enum {
	TYPE_GPIOA=1,
	TYPE_GPIOB=2,
	TYPE_GPIOC=3,
	TYPE_GPIOD=4,
	TYPE_GPIOE=5,
	TYPE_GPIOF=6,
	TYPE_GPIOG=7,
	TYPE_GPIOH=8,
	TYPE_GPIOI=9
} t_GPIO_TYPE;

typedef enum {
	PR_GPIO_MODE_INPUT = 0U,
	PR_GPIO_MODE_OUTPUT = 1U,
	PR_GPIO_MODE_ALTERNATIVE = 2U,
	PR_GPIO_MODE_ANALOG = 3U
} t_GPIO_MODE;

typedef struct t_GPIO {
	char *name;
	t_GPIO_TYPE type;
	uint8_t pin;
} t_GPIO;

#endif
