#include "display/display.h"
#include "games/snake/logic.h"
#include "games/snake/display.h"

/* called every frame */
extern void draw_snake(t_display *display, t_snake_state state)
{
	draw_clear(display, SNAKE_BACKGROUND);
	/* draw in buffer accoridng to state */
	display_flush_fb(display);
}
