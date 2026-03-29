#include "standard.h"
#include "uart.h"
#include "gpio.h"
#include "command.h"

static bool	get_gpio_funcsel(const char *s, uint32_t *value)
{
	if (!strcmp(s, "GPIO_INPUT"))
		*value = GPIO_INPUT;
	else if (!strcmp(s, "GPIO_OUTPUT"))
		*value = GPIO_OUTPUT;
	else if (!strcmp(s, "GPIO_ALT5"))
		*value = GPIO_ALT5;
	else if (!strcmp(s, "GPIO_ALT4"))
		*value = GPIO_ALT4;
	else if (!strcmp(s, "GPIO_ALT0"))
		*value = GPIO_ALT0;
	else if (!strcmp(s, "GPIO_ALT1"))
		*value = GPIO_ALT1;
	else if (!strcmp(s, "GPIO_ALT2"))
		*value = GPIO_ALT2;
	else if (!strcmp(s, "GPIO_ALT3"))
		*value = GPIO_ALT3;
	else
		return false;
	return true;
}

static bool	get_gpio_pull(const char *s, uint32_t *value)
{
	if (!strcmp(s, "GPIO_PULL_OFF"))
		*value = GPIO_PULL_OFF;
	else if (!strcmp(s, "GPIO_PULL_DOWN"))
		*value = GPIO_PULL_DOWN;
	else if (!strcmp(s, "GPIO_PULL_UP"))
		*value = GPIO_PULL_UP;
	else
		return false;
	return true;
}

static uint32_t	split_args(char *buffer, char *argv[], uint32_t max_args)
{
	uint32_t	argc;

	argc = 0;
	while (*buffer && argc < max_args) {
		while (*buffer == ' ')
			buffer++;
		if (!*buffer)
			break;
		argv[argc++] = buffer;
		while (*buffer && *buffer != ' ')
			buffer++;
		if (*buffer) {
			*buffer = '\0';
			buffer++;
		}
	}
	return argc;
}

static t_command_status	execute_cmd(char buffer[BUFFER_SIZE])
{
	char		*argv[4];
	uint32_t	argc;
	uint32_t	pin;
	uint32_t	value;

	argc = split_args(buffer, argv, 4u);
	if (argc == 0u)
		return FOUND;
	if (!strcmp(argv[0], "exit"))
		return EXIT;
	else if (!strcmp(argv[0], "gpio_set_func") && argc == 3u) {
		if ((pin = atoui(argv[1])) > GPIO_MAX)
			return UNKNOWN;
		if (!get_gpio_funcsel(argv[2], &value))
			return UNKNOWN;
		gpio_set_func(pin, value);
		return FOUND;
	}
	else if (!strcmp(argv[0], "gpio_write") && argc == 3u) {
		if ((pin = atoui(argv[1])) > GPIO_MAX)
			return UNKNOWN;
		value = atoui(argv[2]);
		if (value != 0u && value != 1u)
			return UNKNOWN;
		gpio_write(pin, value);
		return FOUND;
	}
	else if (!strcmp(argv[0], "gpio_set_pull") && argc == 3u) {
		if ((pin = atoui(argv[1])) > GPIO_MAX)
			return UNKNOWN;
		if (!get_gpio_pull(argv[2], &value))
			return UNKNOWN;
		gpio_set_pull(pin, value);
		return FOUND;
	}
	return UNKNOWN;
}

extern void	wait_cmd(uintptr_t t)
{
	char				buffer[BUFFER_SIZE];
	uint32_t			index;
	char				c;
	t_command_status	s;

	index = 0;
	uart_putstr(t, "> ");
	while (1) {
		c = uart_getc(t);
		if ((c == '\b' || c == 127) && index > 0) {
			index--;
			uart_putstr(t, "\b \b");
		}
		else if (c == '\r' || c == '\n') {
			uart_putstr(t, "\r\n");
			buffer[index] = 0;
			if (index == 0) {
				uart_putstr(t, "> ");
				continue;
			}
			s = execute_cmd(buffer);
			index = 0;
			if (s == EXIT)
				return;
			if (s == UNKNOWN)
				uart_putstr(t, "unknown command\r\n");
			uart_putstr(t, "> ");
		}
		else if (index < BUFFER_SIZE - 1) {
			buffer[index++] = c;
			uart_putc(t, c);
		}
	}
}
