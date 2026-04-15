#include "display.h"

void	display_bind(t_display *display, void *driver,
		const t_display_ops *ops)
{
	if (display == 0)
		return ;
	display->driver = driver;
	display->ops = ops;
}

bool	display_init(t_display *display)
{
	if (display == 0 || display->ops == 0 || display->ops->init == 0)
		return (false);
	return (display->ops->init(display));
}

void	display_reset(t_display *display)
{
	if (display == 0 || display->ops == 0 || display->ops->reset == 0)
		return ;
	display->ops->reset(display);
}

void	display_set_window(t_display *display, uint16_t x0, uint16_t y0,
		uint16_t x1, uint16_t y1)
{
	if (display == 0 || display->ops == 0 || display->ops->set_window == 0)
		return ;
	display->ops->set_window(display, x0, y0, x1, y1);
}

void	display_write_pixels(t_display *display, const uint16_t *pixels,
		uint32_t count)
{
	if (display == 0 || display->ops == 0 || display->ops->write_pixels == 0)
		return ;
	display->ops->write_pixels(display, pixels, count);
}

void	display_write_color(t_display *display, uint16_t color, uint32_t count)
{
	if (display == 0 || display->ops == 0 || display->ops->write_color == 0)
		return ;
	display->ops->write_color(display, color, count);
}
