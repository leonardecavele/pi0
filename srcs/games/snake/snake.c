#include "drivers/uart.h"
#include "helpers/time.h"
#include "helpers/math.h"
#include "helpers/random.h"
#include "games/snake/snake.h"
#include "games/snake/display.h"
#include "games/snake/logic.h"
#include "system/buttons.h"
#include "display/display.h"
#include "display/draw.h"

static void update_game(t_snake_state *state, uint32_t elapsed_us)
{
	static uint32_t total_elapsed_us = 0;

	if (button_left()) {
		if (!(state->direction.v1 == 1 && state->direction.v2 == 0)) {
			state->direction = (t_vec2){-1, 0};
			uart_printf(BCM2835_UART0, "LEFT\r\n");
		}
	}
	if (button_up()) {
		if (!(state->direction.v1 == 0 && state->direction.v2 == 1)) {
			state->direction = (t_vec2){0, -1};
			uart_printf(BCM2835_UART0, "UP\r\n");
		}
	}
	if (button_right()) {
		if (!(state->direction.v1 == -1 && state->direction.v2 == 0)) {
			state->direction = (t_vec2){1, 0};
			uart_printf(BCM2835_UART0, "RIGHT\r\n");
		}
	}
	if (button_down()) {
		if (!(state->direction.v1 == 0 && state->direction.v2 == -1)) {
			state->direction = (t_vec2){0, 1};
			uart_printf(BCM2835_UART0, "DOWN\r\n");
		}
	}

	total_elapsed_us += elapsed_us;
	if (total_elapsed_us < SNAKE_SPEED_US)
		return;
	total_elapsed_us -= SNAKE_SPEED_US;

	t_vec2 head_pos = state->body[state->head];

	state->body[state->head] = (t_vec2){
		head_pos.v1 + state->direction.v1, head_pos.v2 + state->direction.v2
	};
	if (head_pos.v1 < 0)
		state->body[state->head].v1 = GRID_WIDTH - 1;
	if (head_pos.v1 >= GRID_WIDTH)
		state->body[state->head].v1 = 0;
	if (head_pos.v2 < 0)
		state->body[state->head].v2 = GRID_HEIGHT - 1;
	if (head_pos.v2 >= GRID_HEIGHT)
		state->body[state->head].v2 = 0;
}

extern void snake(t_display *display)
{
	uint16_t cell_size = min(
		display->width / GRID_WIDTH, display->height / GRID_HEIGHT
	);
	t_snake_display snake_display = {
		.cell_size = cell_size,
		.offset_x = (display->width - (GRID_WIDTH * cell_size)) / 2u,
		.offset_y = (display->height - (GRID_HEIGHT * cell_size)) / 2u,
		.game_width = GRID_WIDTH * cell_size,
		.game_height = GRID_HEIGHT * cell_size
	};

	t_snake_state state = {
		.alive = true,
		.length = 1,
		.head = 0,
		.direction = {1, 0},
		.body = {
			[0] = {GRID_WIDTH / 2, GRID_HEIGHT / 2}
		}
	};

	uint32_t excess = 0u;
	uint32_t elapsed_us = 0u;
	while (1) {
		if (snake_display.freeze) {
			snake_display.freeze--;
			continue;
		}
		uint32_t start_us = get_time_us();
		update_game(&state, elapsed_us);
		if (state.alive == false)
			snake_display.freeze = 20; //maybe edit
		draw_snake(display, &snake_display, state);
		/* stabilize frame rate */
		elapsed_us = (get_time_us() - start_us) + excess;
		if (elapsed_us < FRAME_US) {
			usleep(FRAME_US - elapsed_us);
			excess = 0u;
		}
		else
			excess = elapsed_us - FRAME_US;
	}
}
