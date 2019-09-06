//#ifndef __CONFIG_H
//#define __CONFIG_H
#include "gpios.h"

// STM32F407 free pins
const t_GPIO a_GPIOS[] = {
	{"PH2",  TYPE_GPIOH, 2},
	{"PH3",  TYPE_GPIOH, 3},

	{"PI8",  TYPE_GPIOI, 8},
	{"PI10", TYPE_GPIOI, 10},

	{"PE2",  TYPE_GPIOE, 2},
	{"PE3",  TYPE_GPIOE, 3},
	{"PE4",  TYPE_GPIOE, 4},
	{"PE5",  TYPE_GPIOE, 5},
	{"PE6",  TYPE_GPIOE, 6}
};

//#endif
