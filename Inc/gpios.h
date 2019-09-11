#ifndef __GPIOS_H
#define __GPIOS_H

//#include <ctype.h>
//#include <string.h>
//#include <stddef.h>

//#include "stm32f407xx.h"
//#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_gpio.h"
#include "tm_stm32_gpio.h"

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

typedef struct s_GPIO {
	char *name;
	t_GPIO_TYPE type;
	uint16_t pin;
} t_GPIO;

#endif
