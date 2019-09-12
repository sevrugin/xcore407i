#ifndef MODEL_BUTTON_H_
#define MODEL_BUTTON_H_

#include "gpios.h"

#define DEBOUNCE 20          // ms debounce period to prevent flickering when pressing or releasing the button
#define DCLICK_MS 250            // max ms between clicks for a double click event
#define LONG_CLICK_MS 1000        // ms hold period: how long to wait for press+hold event
#define HOLD_EVENT_MS 500		// ms to catch event on hold

typedef enum {
	BUTTON_STATUS_FREE,
	BUTTON_STATUS_DEBOUNCE,
	BUTTON_STATUS_PRESS,
	BUTTON_STATUS_DOUBLE_PRESS,
	BUTTON_STATUS_RELEASE,
	BUTTON_STATUS_LONG_HOLD,
} e_BUTTON_STATUS;

typedef enum {
	EVENT_BUTTON_PRESSED,
	EVENT_BUTTON_CLICKED,
	EVENT_BUTTON_DOUBLE_CLICKED,
	EVENT_BUTTON_HOLD,
	EVENT_BUTTON_LONG_CLICKED,
} e_BUTTON_EVENT;

typedef struct s_Button {
	char id[10];
	char name[10];
	t_GPIO *gpio;
	int time;
	void (*loop)(self);

	e_BUTTON_STATUS _currentStatus;
	GPIO_PinState 	_lowState;
	long _lastActionTime;

} t_Button;

#endif /* MODEL_BUTTON_H_ */
