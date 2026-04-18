#include "display/draw.h"

static bool	draw_clip_rectangle(
	t_display *display, uint16_t *x, uint16_t *y,
	uint16_t *width, uint16_t *height
)
{
	if (display == 0 || display->fb == 0 || x == 0 || y == 0
		|| width == 0 || height == 0)
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

extern void	draw_pixel(
	t_display *display, uint16_t x, uint16_t y, uint16_t color
)
{
	if (display == 0 || display->fb == 0)
		return ;
	if (x >= display->width || y >= display->height)
		return ;
	display->fb[(uint32_t)y * display->width + x] = color;
}

extern void	draw_hline(
	t_display *display, uint16_t x, uint16_t y, uint16_t width, uint16_t color
)
{
	uint16_t	i;
	uint16_t	height;
	uint32_t	index;

	height = 1u;
	if (draw_clip_rectangle(display, &x, &y, &width, &height) == false)
		return ;
	index = (uint32_t)y * display->width + x;
	i = 0u;
	while (i < width)
	{
		display->fb[index + i] = color;
		i++;
	}
}

extern void	draw_vline(
	t_display *display, uint16_t x, uint16_t y, uint16_t height, uint16_t color
)
{
	uint16_t	i;
	uint16_t	width;

	width = 1u;
	if (draw_clip_rectangle(display, &x, &y, &width, &height) == false)
		return ;
	i = 0u;
	while (i < height)
	{
		display->fb[(uint32_t)(y + i) * display->width + x] = color;
		i++;
	}
}

extern void	draw_fill_rectangle(
	t_display *display, uint16_t x, uint16_t y,
	uint16_t width, uint16_t height, uint16_t color
)
{
	uint16_t	row;
	uint16_t	col;
	uint32_t	index;

	if (draw_clip_rectangle(display, &x, &y, &width, &height) == false)
		return ;
	row = 0u;
	while (row < height)
	{
		index = (uint32_t)(y + row) * display->width + x;
		col = 0u;
		while (col < width)
		{
			display->fb[index + col] = color;
			col++;
		}
		row++;
	}
}

extern void	draw_rectangle(
	t_display *display, uint16_t x, uint16_t y,
	uint16_t width, uint16_t height, uint16_t color
)
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

extern void	draw_square(
	t_display *display, uint16_t x, uint16_t y, uint16_t size, uint16_t color
)
{
	draw_rectangle(display, x, y, size, size, color);
}

extern void	draw_fill_square(
	t_display *display, uint16_t x, uint16_t y, uint16_t size, uint16_t color
)
{
	draw_fill_rectangle(display, x, y, size, size, color);
}

static void	draw_circle_points(
	t_display *display, int16_t cx, int16_t cy,
	int16_t x, int16_t y, uint16_t color
)
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

extern void	draw_circle(
	t_display *display, int16_t cx, int16_t cy, int16_t radius, uint16_t color
)
{
	int16_t	x;
	int16_t	y;
	int16_t	error;

	if (display == 0 || display->fb == 0 || radius < 0)
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

extern void	draw_clear(t_display *display, uint16_t color)
{
	if (display == 0 || display->fb == 0)
		return ;
	draw_fill_rectangle(
		display, 0u, 0u, display->width, display->height, color
	);
}
