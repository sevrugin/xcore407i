#ifndef __SERIAL_H
#define __SERIAL_H

#define UART_STATUS_INPUT 0
#define UART_STATUS_ARROW 1
#define UART_STATUS_LOGS 2

#include <ctype.h>
#include <string.h>
#include <stddef.h>

void executeSerialCommand(char *str);

#endif
