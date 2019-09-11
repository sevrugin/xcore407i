#ifndef MODEL_BUTTON_H_
#define MODEL_BUTTON_H_

#include "gpios.h"

typedef enum {
	BUTTON_STATUS_FREE
} e_BUTTON_STATUS;

typedef struct s_Button {
	char id[10];
	char name[10];
	t_GPIO *gpio;
	int time;
	e_BUTTON_STATUS status;
	void (*loop)(self);
} t_Button;

#endif /* MODEL_BUTTON_H_ */
