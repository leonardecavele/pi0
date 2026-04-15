#ifndef DISPLAY_H
#define DISPLAY_H

#include "helpers/standard.h"

typedef struct s_display t_display;

typedef struct s_display_ops
{
	bool	(*init)(t_display *display);
	void	(*reset)(t_display *display);
	void	(*set_window)(t_display *display, uint16_t x0, uint16_t y0,
			uint16_t x1, uint16_t y1);
	void	(*write_pixels)(t_display *display, const uint16_t *pixels,
			uint32_t count);
	void	(*write_color)(t_display *display, uint16_t color, uint32_t count);
} 	t_display_ops;

typedef struct s_display
{
	uint16_t		width;
	uint16_t		height;
	uint16_t		x_offset;
	uint16_t		y_offset;
	void			*driver;
	const t_display_ops	*ops;
} 	t_display;

void	display_bind(t_display *display, void *driver,
		const t_display_ops *ops);
bool	display_init(t_display *display);
void	display_reset(t_display *display);
void	display_set_window(t_display *display, uint16_t x0, uint16_t y0,
		uint16_t x1, uint16_t y1);
void	display_write_pixels(t_display *display, const uint16_t *pixels,
		uint32_t count);
void	display_write_color(t_display *display, uint16_t color, uint32_t count);

#endif
