#ifndef DRAW_H
#define DRAW_H

#include "display/display.h"

#define RGB565(r, g, b) \
	(uint16_t)((((uint16_t)((r) & 0x1fu)) << 11) \
	| (((uint16_t)((g) & 0x3fu)) << 5) \
	| ((uint16_t)((b) & 0x1fu)))

void	draw_pixel(t_display *display, uint16_t x, uint16_t y, uint16_t color);
void	draw_hline(
	t_display *display, uint16_t x, uint16_t y, uint16_t width, uint16_t color
);
void	draw_vline(
	t_display *display, uint16_t x, uint16_t y, uint16_t height, uint16_t color
);
void	draw_fill_rect(
	t_display *display, uint16_t x, uint16_t y,
	uint16_t width, uint16_t height, uint16_t color
);
void	draw_rect(
	t_display *display, uint16_t x, uint16_t y,
	uint16_t width, uint16_t height, uint16_t color
);
void	draw_square(
	t_display *display, uint16_t x, uint16_t y, uint16_t size, uint16_t color
);
void	draw_fill_square(
	t_display *display, uint16_t x, uint16_t y, uint16_t size, uint16_t color
);
void	draw_circle(
	t_display *display, int16_t cx, int16_t cy, int16_t radius, uint16_t color
);
void	draw_clear(t_display *display, uint16_t color);

#endif
