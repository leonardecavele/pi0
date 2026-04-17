#include "display/display.h"

extern void	display_init(t_display *display)
{
	display->fn->init(display);
}

extern void	display_reset(t_display *display)
{
	display->fn->reset(display);
}

extern void	display_set_window(
	t_display *display, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1
)
{
	display->fn->set_window(display, x0, y0, x1, y1);
}

extern void	display_write_pixels(
	t_display *display, const uint16_t *pixels, uint32_t count
)
{
	display->fn->write_pixels(display, pixels, count);
}

extern void	display_write_color(t_display *display, uint16_t color, uint32_t count)
{
	display->fn->write_color(display, color, count);
}
