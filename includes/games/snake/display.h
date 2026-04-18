#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "display/display.h"
#include "games/snake/logic.h"

typedef enum e_snake_colors
{
	SNAKE_BACKGROUND = 0xFFFFu
}	t_snake_colors;

typedef struct s_snake_display
{
	uint16_t	cell_size;
	uint16_t	offset_x;
	uint16_t	offset_y;
	uint16_t	game_width;
	uint16_t	game_height;
}	t_snake_display;

void draw_snake(t_display *display, t_snake_state state);

#endif
