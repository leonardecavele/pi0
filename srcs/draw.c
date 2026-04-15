#include "draw.h"

static bool	draw_clip_rect(t_display *display, uint16_t *x, uint16_t *y,
		uint16_t *width, uint16_t *height)
{
	if (display == 0 || x == 0 || y == 0 || width == 0 || height == 0)
		return (false);
	if (*width == 0u || *height == 0u)
		return (false);
	if (*x >= display->width || *y >= display->height)
		return (false);
	if ((uint32_t)(*x + *width) > display->width)
		*width = (uint16_t)(display->width - *x);
	if ((uint32_t)(*y + *height) > display->height)
		*height = (uint16_t)(display->height - *y);
	if (*width == 0u || *height == 0u)
		return (false);
	return (true);
}

void	draw_pixel(t_display *display, uint16_t x, uint16_t y, uint16_t color)
{
	if (display == 0 || x >= display->width || y >= display->height)
		return ;
	display_set_window(display, x, y, x, y);
	display_write_color(display, color, 1u);
}

void	draw_hline(t_display *display, uint16_t x, uint16_t y,
		uint16_t width, uint16_t color)
{
	uint16_t	height;

	height = 1u;
	if (draw_clip_rect(display, &x, &y, &width, &height) == false)
		return ;
	display_set_window(display, x, y, (uint16_t)(x + width - 1u), y);
	display_write_color(display, color, width);
}

void	draw_vline(t_display *display, uint16_t x, uint16_t y,
		uint16_t height, uint16_t color)
{
	uint16_t	width;

	width = 1u;
	if (draw_clip_rect(display, &x, &y, &width, &height) == false)
		return ;
	display_set_window(display, x, y, x, (uint16_t)(y + height - 1u));
	display_write_color(display, color, height);
}

void	draw_fill_rect(t_display *display, uint16_t x, uint16_t y,
		uint16_t width, uint16_t height, uint16_t color)
{
	if (draw_clip_rect(display, &x, &y, &width, &height) == false)
		return ;
	display_set_window(display, x, y,
		(uint16_t)(x + width - 1u), (uint16_t)(y + height - 1u));
	display_write_color(display, color, (uint32_t)width * (uint32_t)height);
}

void	draw_rect(t_display *display, uint16_t x, uint16_t y,
		uint16_t width, uint16_t height, uint16_t color)
{
	if (width == 0u || height == 0u)
		return ;
	draw_hline(display, x, y, width, color);
	if (height > 1u)
		draw_hline(display, x, (uint16_t)(y + height - 1u), width, color);
	if (height > 2u)
	{
		draw_vline(display, x, (uint16_t)(y + 1u), (uint16_t)(height - 2u), color);
		if (width > 1u)
			draw_vline(display, (uint16_t)(x + width - 1u),
				(uint16_t)(y + 1u), (uint16_t)(height - 2u), color);
	}
}

void	draw_square(t_display *display, uint16_t x, uint16_t y,
		uint16_t size, uint16_t color)
{
	draw_rect(display, x, y, size, size, color);
}

void	draw_fill_square(t_display *display, uint16_t x, uint16_t y,
		uint16_t size, uint16_t color)
{
	draw_fill_rect(display, x, y, size, size, color);
}

static void	draw_circle_points(t_display *display, int16_t cx, int16_t cy,
		int16_t x, int16_t y, uint16_t color)
{
	if (cx + x >= 0 && cy + y >= 0)
		draw_pixel(display, (uint16_t)(cx + x), (uint16_t)(cy + y), color);
	if (cx - x >= 0 && cy + y >= 0)
		draw_pixel(display, (uint16_t)(cx - x), (uint16_t)(cy + y), color);
	if (cx + x >= 0 && cy - y >= 0)
		draw_pixel(display, (uint16_t)(cx + x), (uint16_t)(cy - y), color);
	if (cx - x >= 0 && cy - y >= 0)
		draw_pixel(display, (uint16_t)(cx - x), (uint16_t)(cy - y), color);
	if (cx + y >= 0 && cy + x >= 0)
		draw_pixel(display, (uint16_t)(cx + y), (uint16_t)(cy + x), color);
	if (cx - y >= 0 && cy + x >= 0)
		draw_pixel(display, (uint16_t)(cx - y), (uint16_t)(cy + x), color);
	if (cx + y >= 0 && cy - x >= 0)
		draw_pixel(display, (uint16_t)(cx + y), (uint16_t)(cy - x), color);
	if (cx - y >= 0 && cy - x >= 0)
		draw_pixel(display, (uint16_t)(cx - y), (uint16_t)(cy - x), color);
}

void	draw_circle(t_display *display, int16_t cx, int16_t cy,
		int16_t radius, uint16_t color)
{
	int16_t	x;
	int16_t	y;
	int16_t	error;

	if (display == 0 || radius < 0)
		return ;
	x = radius;
	y = 0;
	error = 1 - radius;
	while (x >= y)
	{
		draw_circle_points(display, cx, cy, x, y, color);
		++y;
		if (error < 0)
			error += (int16_t)(2 * y + 1);
		else
		{
			--x;
			error += (int16_t)(2 * (y - x) + 1);
		}
	}
}

void	draw_clear(t_display *display, uint16_t color)
{
	if (display == 0)
		return ;
	draw_fill_rect(display, 0u, 0u, display->width, display->height, color);
}
