#include "helpers/time.h"
#include "helpers/math.h"
#include "games/snake/snake.h"
#include "games/snake/display.h"
#include "games/snake/logic.h"
#include "system/buttons.h"
#include "display/display.h"
#include "display/draw.h"

#include "drivers/uart.h"
static void update_game(t_snake_state *state)
{
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

	t_vec2 head_pos = state->body[state->head];

	if (
		head_pos.v1 + state->direction.v1 < 0
		|| head_pos.v1 + state->direction.v1 >= GRID_WIDTH
		|| head_pos.v2 + state->direction.v2 < 0
		|| head_pos.v2 + state->direction.v2 >= GRID_HEIGHT
	)
		state->alive = false;
	else
		state->body[state->head] = (t_vec2){
			head_pos.v1 + state->direction.v1, head_pos.v2 + state->direction.v2
		};
	uart_printf(
		BCM2835_UART0, "x %d y %d\r\n", state->direction.v1, state->direction.v2
	);
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
	while (1) {
		uint32_t start_us = get_time_us();
		draw_snake(display, &snake_display, state);
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
