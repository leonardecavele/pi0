#include "display.h"
#include "time.h"

extern void	display_init(void)
{
	gpio_set_func(DISPLAY_DC_GPIO, GPIO_OUTPUT);
	gpio_set_func(DISPLAY_RST_GPIO, GPIO_OUTPUT);
	gpio_set_pull(DISPLAY_DC_GPIO, GPIO_PULL_OFF);
	gpio_set_pull(DISPLAY_RST_GPIO, GPIO_PULL_OFF);
	gpio_write(DISPLAY_DC_GPIO, true);
	gpio_write(DISPLAY_RST_GPIO, true);
}

extern void	display_reset(void)
{
	gpio_write(DISPLAY_RST_GPIO, true);
	usleep(5000u);
	gpio_write(DISPLAY_RST_GPIO, false);
	usleep(5000u);
	gpio_write(DISPLAY_RST_GPIO, true);
	usleep(5000u);
}

extern void	display_set_mode(t_display_mode mode)
{
	if (mode == DISPLAY_COMMAND)
		gpio_write(DISPLAY_DC_GPIO, false);
	else
		gpio_write(DISPLAY_DC_GPIO, true);
}
