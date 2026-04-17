#ifndef MAPPING_H
#define MAPPING_H

#include "helpers/standard.h"

typedef enum e_gpio_mapping
{
	SPI0_CE0_GPIO = 8u,
	SPI0_MOSI_GPIO = 10u,
	SPI0_SCLK_GPIO = 11u,
	UART_TXD_GPIO = 14u,
	UART_RXD_GPIO = 15u,
	DISPLAY_RST_GPIO = 22u,
	LEFT_BUTTON_GPIO = 23u,
	UP_BUTTON_GPIO = 24u,
	RIGHT_BUTTON_GPIO = 25u,
	DOWN_BUTTON_GPIO = 26u,
	DISPLAY_DC_GPIO = 27u
} t_gpio_mapping;

void mapping_buttons(void);
void mapping_uart(void);
void mapping_spi(void);
void mapping_display(void);

#endif
