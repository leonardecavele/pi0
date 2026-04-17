#include "display.h"

void	display_bind(
	t_display *display, void *driver, const t_display_fn *fn
)
{
	if (display == 0)
		return ;
	display->driver = driver;
	display->fn = fn;
}

bool	display_init(t_display *display)
{
	display->fn->init(display);
}

void	display_reset(t_display *display)
{
	display->fn->reset(display);
}

void	display_set_window(
	t_display *display, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1
)
{
	display->fn->set_window(display, x0, y0, x1, y1);
}

void	display_write_pixels(
	t_display *display, const uint16_t *pixels, uint32_t count
)
{
	display->fn->write_pixels(display, pixels, count);
}

void	display_write_color(t_display *display, uint16_t color, uint32_t count)
{
	display->fn->write_color(display, color, count);
}
