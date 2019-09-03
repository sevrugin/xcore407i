#ifndef __GPIOS_H
#define __GPIOS_H

#include "stm32f4xx_hal_gpio.h"

typedef struct {
	char *name;
	GPIO_TypeDef *GPIOx;
	uint16_t *pin;
} t_GPIO;

t_GPIO gpios = {
		{"PA1", GPIOA, GPIO_PIN_1}
};

#endif
