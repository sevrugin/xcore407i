
#include "Button.h"

extern const t_GPIO *a_GPIOS;
extern uint16_t GPIOS_COUNT;
extern t_Button *PR_buttons;
extern uint16_t PR_Buttons_count;

void PR_Buttons_Init(t_Button **PR_buttons, uint16_t *PR_Buttons_count);
uint8_t PR_Button_isPressed(t_Button *button);
void PR_Buttons_loop();

void PR_Buttons_loop()
{
	for (uint16_t i = 0; i < PR_Buttons_count; i++) {
		PR_Button_loop(&PR_buttons[i]);
	}
}

void PR_Button_loop(t_Button *button)
{

	switch (button->_currentStatus) {
		case BUTTON_STATUS_FREE:
			if (PR_Button_isPressed(button)) {
				button->_currentStatus = BUTTON_STATUS_DEBOUNCE;
				button->_lastActionTime = HAL_GetTick();
			}
			break;
		case BUTTON_STATUS_DEBOUNCE:
			if (PR_Button_isPressed(button)) {
				if ((HAL_GetTick() - button->_lastActionTime) > DEBOUNCE) {
					button->_currentStatus = BUTTON_STATUS_PRESS;
					button->_lastActionTime = HAL_GetTick();
					// todo: pressedEvent
					event(button, EVENT_BUTTON_PRESSED);
				}
			} else {
				button->_currentStatus = BUTTON_STATUS_FREE;
				button->_lastActionTime = -1;
			}
			break;
		case BUTTON_STATUS_PRESS:
			if (PR_Button_isPressed(button)) { // waiting for long action
				if ((HAL_GetTick() - button->_lastActionTime) > LONG_CLICK_MS) {
					// todo: longEvent
					event(button, EVENT_BUTTON_LONG_CLICKED);
					button->_currentStatus = BUTTON_STATUS_LONG_HOLD;
					button->_lastActionTime = HAL_GetTick();
				}
			} else {
				if ((HAL_GetTick() - button->_lastActionTime) > DEBOUNCE) { // released
					button->_currentStatus = BUTTON_STATUS_RELEASE;
					button->_lastActionTime = HAL_GetTick();
				}
			}
			break;
		case BUTTON_STATUS_RELEASE:
			if (PR_Button_isPressed(button)) {
				if ((HAL_GetTick() - button->_lastActionTime) > DEBOUNCE && (HAL_GetTick() - button->_lastActionTime) < DCLICK_MS) {
					button->_currentStatus = BUTTON_STATUS_DOUBLE_PRESS;
					button->_lastActionTime = HAL_GetTick();
				}
			} else {
				if ((HAL_GetTick() - button->_lastActionTime) > DCLICK_MS) {
					// todo: clickedEvent
					event(button, EVENT_BUTTON_CLICKED);
					button->_currentStatus = BUTTON_STATUS_FREE;
					button->_lastActionTime = -1;
				}
			}
			break;
		case BUTTON_STATUS_LONG_HOLD:
			if (PR_Button_isPressed(button)) {
				if ((HAL_GetTick() - button->_lastActionTime) > HOLD_EVENT_MS) {
					// todo: holdEvent
					event(button, EVENT_BUTTON_HOLD);
					button->_lastActionTime = HAL_GetTick();
				}
			} else {
				if ((HAL_GetTick() - button->_lastActionTime) > DEBOUNCE) {
					button->_currentStatus = BUTTON_STATUS_FREE;
					button->_lastActionTime = -1;
				}
			}
			break;
		case BUTTON_STATUS_DOUBLE_PRESS:
			if (! PR_Button_isPressed(button)) {
				if ((HAL_GetTick() - button->_lastActionTime) > DEBOUNCE) {
					// todo: doubleEvent
					event(button, EVENT_BUTTON_DOUBLE_CLICKED);
					button->_currentStatus = BUTTON_STATUS_FREE;
					button->_lastActionTime = -1;
				}
			}
			break;
	}
}

t_Button newButton(char *name, char *pin, GPIO_PinState lowState)
{
	t_Button button;

	memcpy(button.id, name, strlen(name)+1);
	memcpy(button.name, name, strlen(name)+1);
	button.time = NULL;
	button._currentStatus = BUTTON_STATUS_FREE;
	button._lowState = lowState;
	button.loop = &PR_Button_loop;
	button._lastActionTime = -1;

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

	_PR_buttons[0] = newButton("btn1", "PE2", GPIO_PIN_SET);
	_PR_buttons[1] = newButton("btn2", "PE3", GPIO_PIN_SET);
	_PR_buttons[2] = newButton("btn3", "PE4", GPIO_PIN_SET);
	_PR_buttons[3] = newButton("btn4", "PE5", GPIO_PIN_SET);
	_PR_buttons[4] = newButton("btn5", "PE6", GPIO_PIN_SET);

	*PR_buttons = _PR_buttons;
}

GPIO_PinState PR_Button_read(t_Button *button)
{
	t_GPIO *gpio = button->gpio;
	GPIO_TypeDef *GPIOx = PR_GetGPIOx_byType(gpio->type);

	return PR_getGPIOvalue(GPIOx, gpio->pin);
}

uint8_t PR_Button_isPressed(t_Button *button)
{
	GPIO_PinState state = PR_Button_read(button);

	return (button->_lowState == state)? 0: 1;
}

void event(t_Button *button, e_BUTTON_EVENT event)
{
	info("Event for: ");
	info(button->name);
	info("\t");
	switch (event) {
		case EVENT_BUTTON_PRESSED:
			info("pressed");
			break;
		case EVENT_BUTTON_CLICKED:
			info("clicked");
			break;
		case EVENT_BUTTON_DOUBLE_CLICKED:
			info("double clicked");
			break;
		case EVENT_BUTTON_HOLD:
			info("hold");
			break;
		case EVENT_BUTTON_LONG_CLICKED:
			info("long clicked");
			break;
	}
	info ("\n\r");
}
