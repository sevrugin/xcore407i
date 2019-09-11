
#include "Button.h"

extern const t_GPIO *a_GPIOS;
extern uint16_t GPIOS_COUNT;

void PR_Buttons_Init(t_Button **PR_buttons, uint16_t *PR_Buttons_count);

void loop(t_Button *button)
{
	print("LOOP FOR ");
	print(button->name);
	print("\n\r");
}

t_Button newButton(char *name, char *pin)
{
	t_Button button;

	memcpy(button.id, name, strlen(name)+1);
	memcpy(button.name, name, strlen(name)+1);
	button.time = NULL;
	button.status = BUTTON_STATUS_FREE;
	button.loop = &loop;

	for (int i = 0; i < GPIOS_COUNT; i++) {
		if (strcmp(pin, a_GPIOS[i].name) == 0) {
			button.gpio = &a_GPIOS[i];
			PR_GPIO_SetMode(button.gpio, TM_GPIO_Mode_IN);
			break;
		}
	}

	return button;
}

void PR_Buttons_Init(t_Button **PR_buttons, uint16_t *PR_Buttons_count)
{
	*PR_Buttons_count = 5;
	t_Button *_PR_buttons = (t_Button *)malloc(*PR_Buttons_count * sizeof(t_Button));

	_PR_buttons[0] = newButton("btn1", "PE2");
	_PR_buttons[1] = newButton("btn2", "PE3");
	_PR_buttons[2] = newButton("btn3", "PE4");
	_PR_buttons[3] = newButton("btn4", "PE5");
	_PR_buttons[4] = newButton("btn5", "PE6");

	*PR_buttons = _PR_buttons;
}
