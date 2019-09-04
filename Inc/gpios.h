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

#ifndef GPIO_PIN_0
#define GPIO_PIN_0		((uint16_t)0x0001)
#define GPIO_PIN_1		((uint16_t)0x0002)
#define GPIO_PIN_2		((uint16_t)0x0004)
#define GPIO_PIN_3		((uint16_t)0x0008)
#define GPIO_PIN_4		((uint16_t)0x0010)
#define GPIO_PIN_5		((uint16_t)0x0020)
#define GPIO_PIN_6		((uint16_t)0x0040)
#define GPIO_PIN_7		((uint16_t)0x0080)
#define GPIO_PIN_8		((uint16_t)0x0100)
#define GPIO_PIN_9		((uint16_t)0x0200)
#define GPIO_PIN_10		((uint16_t)0x0400)
#define GPIO_PIN_11		((uint16_t)0x0800)
#define GPIO_PIN_12		((uint16_t)0x1000)
#define GPIO_PIN_13		((uint16_t)0x2000)
#define GPIO_PIN_14		((uint16_t)0x4000)
#define GPIO_PIN_15		((uint16_t)0x8000)
#define GPIO_PIN_ALL	((uint16_t)0xFFFF)
#endif


typedef struct t_GPIO {
	char *name;
	t_GPIO_TYPE type;
	uint16_t pin;
} t_GPIO;

#endif
