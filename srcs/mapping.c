#include "gpio.h"
#include "hardware_specific.h"

extern void mapping_buttons(void)
{
	gpio_set_func(LEFT_BUTTON_GPIO, GPIO_INPUT);
	gpio_set_pull(LEFT_BUTTON_GPIO, GPIO_PULL_UP);
	gpio_event_clear(LEFT_BUTTON_GPIO);
	gpio_enable_falling(LEFT_BUTTON_GPIO);
	gpio_event_clear(LEFT_BUTTON_GPIO);

	gpio_set_func(UP_BUTTON_GPIO, GPIO_INPUT);
	gpio_set_pull(UP_BUTTON_GPIO, GPIO_PULL_UP);
	gpio_event_clear(UP_BUTTON_GPIO);
	gpio_enable_falling(UP_BUTTON_GPIO);
	gpio_event_clear(UP_BUTTON_GPIO);

	gpio_set_func(RIGHT_BUTTON_GPIO, GPIO_INPUT);
	gpio_set_pull(RIGHT_BUTTON_GPIO, GPIO_PULL_UP);
	gpio_event_clear(RIGHT_BUTTON_GPIO);
	gpio_enable_falling(RIGHT_BUTTON_GPIO);
	gpio_event_clear(RIGHT_BUTTON_GPIO);

	gpio_set_func(DOWN_BUTTON_GPIO, GPIO_INPUT);
	gpio_set_pull(DOWN_BUTTON_GPIO, GPIO_PULL_UP);
	gpio_event_clear(DOWN_BUTTON_GPIO);
	gpio_enable_falling(DOWN_BUTTON_GPIO);
	gpio_event_clear(DOWN_BUTTON_GPIO);
}

extern void mapping_uart(uint32_t void)
{
	gpio_set_func(UART_TXD_GPIO, GPIO_ALT0);
	gpio_set_pull(UART_TXD_GPIO, GPIO_PULL_OFF);

	gpio_set_func(UART_RXD_GPIO, GPIO_ALT0);
	gpio_set_pull(UART_RXD_GPIO, GPIO_PULL_OFF);
}

extern void mapping_spi(void)
{
	gpio_set_func(SPI0_CE0_GPIO, GPIO_ALT0);
	gpio_set_func(SPI0_MOSI_GPIO, GPIO_ALT0);
	gpio_set_func(SPI0_SCLK_GPIO, GPIO_ALT0);

	gpio_set_pull(SPI0_CE0_GPIO, GPIO_PULL_OFF);
	gpio_set_pull(SPI0_MOSI_GPIO, GPIO_PULL_OFF);
	gpio_set_pull(SPI0_SCLK_GPIO, GPIO_PULL_OFF);
}

extern void	mapping_display(void)
{
	gpio_set_func(DISPLAY_DC_GPIO, GPIO_OUTPUT);
	gpio_set_func(DISPLAY_RST_GPIO, GPIO_OUTPUT);
	gpio_set_pull(DISPLAY_DC_GPIO, GPIO_PULL_OFF);
	gpio_set_pull(DISPLAY_RST_GPIO, GPIO_PULL_OFF);
	gpio_write(DISPLAY_DC_GPIO, true);
	gpio_write(DISPLAY_RST_GPIO, true);
}
