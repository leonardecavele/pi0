#include "display/display.h"
#include "display/draw.h"
#include "games/snake/logic.h"
#include "games/snake/display.h"

static void draw_game_background(
	t_display *display, t_snake_display *snake_display
)
{
	draw_fill_rectangle(
		display,
		snake_display->offset_x,
		snake_display->offset_y,
		GRID_WIDTH * snake_display->cell_size,
		GRID_HEIGHT * snake_display->cell_size,
		SNAKE_GAME_BACKGROUND
	);
}

/* called every frame */
extern void draw_snake(
	t_display *display, t_snake_display *snake_display, t_snake_state state
)
{
	draw_clear(display, SNAKE_BACKGROUND);
	draw_game_background(display, snake_display);
	display_flush_fb(display);
}
