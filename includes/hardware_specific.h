#ifndef HARDWARE_SPECIFIC_H
#define HARDWARE_SPECIFIC_H

#include "standard.h"

typedef enum e_gpio_mapping
{
	UART_TXD_GPIO = 14u,
	UART_RXD_GPIO = 15u,
	LEFT_BUTTON_GPIO = 23u,
	UP_BUTTON_GPIO = 24u,
	RIGHT_BUTTON_GPIO = 25u,
	DOWN_BUTTON_GPIO = 26u
}	t_gpio_mapping;

void set_up_input_gpio(uint32_t gpio)
void set_up_uart_gpio(uint32_t gpio)

#endif
