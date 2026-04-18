#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "display/display.h"
#include "games/snake/logic.h"

typedef enum e_snake_colors
{
	SNAKE_BACKGROUND = 0xFFFFu
}	t_snake_colors;

void draw_snake(t_display *display, t_snake_state state);

#endif
