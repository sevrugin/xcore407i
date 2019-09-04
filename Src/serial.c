#include "serial.h"
#include "gpios.h"

typedef struct {
	char *name;
	char *description;
	void (*run)();
} t_Command;

void *SR_runGpios();
void *SR_runGpio();
void *SR_runLogs();
void *SR_runHelp(t_Command *self);
void *SR_runVersion();

int PR_UART_STATUS = UART_STATUS_INPUT;
int *SR_getSerialStatus();
void SR_setSerialStatus(int status);

t_Command commands[] = {
		{name: "gpios", description: "Show list of exists GPIO pins", run: &SR_runGpios},
		{name: "gpio", description: "Set or read GPIO status", run: &SR_runGpio},
		{name: "logs", description: "Switch to the 'logs' mode", run: &SR_runLogs},
		{name: "help", description: "Show help message", run: &SR_runHelp},
		{name: "version", description: "Show firmware version", run: &SR_runVersion},
};

#define NKEYS (sizeof(commands)/sizeof(t_Command))

void *SR_runGpios()
{
	#include "config.h"

	int len = (sizeof(a_GPIOS) / sizeof(t_GPIO));
	for (int i = 0; i < len; i++) {
		print(a_GPIOS[i].name);
		print("\n\r");
	}
}

void *SR_runLogs()
{
	print("Logs mode enabled. Type Ctrl+C to disable\n\r");
	SR_setSerialStatus(UART_STATUS_LOGS);
}

/**
 * # > gpio PH1 on/off/get/toggle
 *
 */
void *SR_runGpio()
{
	#include "config.h"

	// 2: pin name
	char *token;
	token = strtok(NULL, " ");
	if (NULL == token) {
		print("Provide GPIO name (e.g. 'PH1') after command \n\r");
		return NULL;
	}
	t_GPIO *gpio = NULL;

	int len = (sizeof(a_GPIOS) / sizeof(t_GPIO));
	for (int i = 0; i < len; i++) {
		if (strcmp(token, a_GPIOS[i].name) == 0) {
			gpio = &a_GPIOS[i];
			break;
		}
	}

	if (NULL == gpio) {
		print("GPIO '");
		print(token);
		print("' not found. Use 'gpios' command to see full GPIOs list\n\r");
		return NULL;
	}

	// 2. get command
	token = strtok(NULL, " ");
	if (NULL == token) {
		print("After GPIO name use commands like on/off/read/toggle \n\r");
		return NULL;
	}
	GPIO_TypeDef *GPIOx = PR_GetGPIOx_byType(gpio->type);

	if (strcmp(token, "on") == 0) {
		HAL_GPIO_WritePin(GPIOx, gpio->pin, GPIO_PIN_SET);
	} else if (strcmp(token, "off") == 0) {
		HAL_GPIO_WritePin(GPIOx, gpio->pin, GPIO_PIN_RESET);
	} else if (strcmp(token, "toggle") == 0) {
		HAL_GPIO_TogglePin(GPIOx, gpio->pin);
	} else if (strcmp(token, "read") == 0) {
		int state = HAL_GPIO_ReadPin(GPIOx, gpio->pin) == GPIO_PIN_SET? 1: 0;
		print(state);
		print("\n\r");
	} else {
		print("Command '");
		print(token);
		print("' not found\n\r");
	}
}


void *SR_runHelp(t_Command *self)
{
	char *token;
	token = strtok(NULL, " ");

	if (NULL == token) {
		for (int i = 0; i < NKEYS; i++) {
			print(commands[i].name);
			print(" - ");
			print(commands[i].description);
			print("\n\r");
		}
	} else {
		int isset = 0;
		for (int i = 0; i < NKEYS; i++) {
			if (strcmp(token, commands[i].name) == 0) {
				isset = 1;
				print(commands[i].name);
				print(" - ");
				print(commands[i].description);
				print("\n\r");
			}
		}
		if (0 == isset) {
			print("Command not found\n\r");
		}
	}
}

void *SR_runVersion()
{
	print("Firmware version: ");
	print(getFwVersion());
	print("\n\r");
}

void SR_execCommand(char *str)
{
	char *token;
	token = strtok(str, " ");

	int isset = 0;
	for (int i = 0; i < NKEYS; i++) {
		if (strcmp(token, commands[i].name) == 0) {
			isset = 1;
			// print(token);
			// print(" OK\r\n");
			if (NULL != commands[i].run) {
				commands[i].run();
			}
			break;
		}
	}
	if (0 == isset) {
		print("Command not found\n\r");
	}
}

int *SR_getSerialStatus()
{
	return PR_UART_STATUS;
}
void SR_setSerialStatus(int status)
{
	PR_UART_STATUS = status;
}
