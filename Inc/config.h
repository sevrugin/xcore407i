//#ifndef __CONFIG_H
//#define __CONFIG_H
#include "gpios.h"

// STM32F407 free pins
const t_GPIO a_GPIOS[] = {
	{"PH2",  TYPE_GPIOH, GPIO_PIN_2},
	{"PH3",  TYPE_GPIOH, GPIO_PIN_3},

	{"PI8",  TYPE_GPIOI, GPIO_PIN_8},
	{"PI10", TYPE_GPIOI, GPIO_PIN_10},

	{"PE2",  TYPE_GPIOE, GPIO_PIN_2},
	{"PE3",  TYPE_GPIOE, GPIO_PIN_3},
	{"PE4",  TYPE_GPIOE, GPIO_PIN_4},
	{"PE5",  TYPE_GPIOE, GPIO_PIN_5},
	{"PE6",  TYPE_GPIOE, GPIO_PIN_6}
};

//#endif
