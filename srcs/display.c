#include "display.h"
#include "mapping.h"
#include "time.h"

void display_reset(void)
{
	gpio_write(DISPLAY_RST_GPIO, true);
	usleep(5000u);
	gpio_write(DISPLAY_RST_GPIO, false);
	usleep(5000u);
	gpio_write(DISPLAY_RST_GPIO, true);
	usleep(5000u);
}

void display_set_mode(t_display_mode mode)
{
	if (mode == DISPLAY_COMMAND)
		gpio_write(DISPLAY_DC_GPIO, false);
	else
		gpio_write(DISPLAY_DC_GPIO, true);
}
