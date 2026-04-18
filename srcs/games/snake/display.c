#include "display/display.h"
#include "display/draw.h"
#include "games/snake/logic.h"
#include "games/snake/display.h"

static void draw_cell(
	t_display *display, t_snake_display *snake_display,
	uint16_t grid_x, uint16_t grid_y, uint16_t color
)
{
	if (grid_x >= GRID_WIDTH || grid_y >= GRID_HEIGHT)
		return ;

	draw_fill_rectangle(
		display,
		snake_display->offset_x + (grid_x * snake_display->cell_size),
		snake_display->offset_y + (grid_y * snake_display->cell_size),
		snake_display->cell_size,
		snake_display->cell_size,
		color
	);
}

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
	draw_cell(display, snake_display, 3, 4, 0x9249);
	draw_cell(display, snake_display, 1, 0, 0x76813);
	draw_cell(display, snake_display, 0, GRID_HEIGHT - 1, 0xBB3A);
	display_flush_fb(display);
}
