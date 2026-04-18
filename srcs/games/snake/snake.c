#include "helpers/time.h"
#include "games/snake/snake.h"
#include "games/snake/display.h"
#include "games/snake/logic.h"
#include "system/buttons.h"
#include "display/display.h"
#include "display/draw.h"

static void update_game(t_snake_state *state)
{
	if (button_left()) {
		;
	}
	if (button_up()) {
		;
	}
	if (button_right()) {
		;
	}
	if (button_down()) {
		;
	}
}

extern void snake(t_display *display)
{
	t_snake_state state = (t_snake_state){0};

	uint32_t excess = 0u;
	while (1) {
		uint32_t start_us = get_time_us();
		draw_snake(display, state);
		update_game(&state);
		/* stabilize frame rate */
		uint32_t elapsed_us = (get_time_us() - start_us) + excess;
		if (elapsed_us < FRAME_US) {
			usleep(FRAME_US - elapsed_us);
			excess = 0u;
		}
		else
			excess = elapsed_us - FRAME_US;
	}
}
