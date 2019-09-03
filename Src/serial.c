#include "serial.h"

typedef struct {
	char *name;
	char *description;
	void (*run)();
} t_Command;

void *SR_runHelp(t_Command *self);
void *SR_runVersion();

t_Command commands[] = {
		{name: "help", description: "Show help message", run: &SR_runHelp},
		{name: "version", description: "Show firmware version", run: &SR_runVersion},
};

#define NKEYS (sizeof(commands)/sizeof(t_Command))

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

