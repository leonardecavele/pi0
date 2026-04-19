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

static void update_buttons(t_snake_state *state)
{
	if (button_left()) {
		uart_printf(BCM2835_UART0, "LEFT\r\n");
		if (!(state->direction.v1 == 1 && state->direction.v2 == 0))
			state->direction = (t_vec2){-1, 0};
	}
	if (button_up()) {
		uart_printf(BCM2835_UART0, "UP\r\n");
		if (!(state->direction.v1 == 0 && state->direction.v2 == 1))
			state->direction = (t_vec2){0, -1};
	}
	if (button_right()) {
		uart_printf(BCM2835_UART0, "RIGHT\r\n");
		if (!(state->direction.v1 == -1 && state->direction.v2 == 0))
			state->direction = (t_vec2){1, 0};
	}
	if (button_down()) {
		uart_printf(BCM2835_UART0, "DOWN\r\n");
		if (!(state->direction.v1 == 0 && state->direction.v2 == -1))
			state->direction = (t_vec2){0, 1};
	}
}

static void update_direction(t_snake_state *state, uint32_t elapsed_us)
{
	static uint32_t total_elapsed_us = 0;
	total_elapsed_us += elapsed_us;
	if (total_elapsed_us < SNAKE_SPEED_US)
		return;
	total_elapsed_us -= SNAKE_SPEED_US;

	t_vec2 head_pos = state->body[state->head];
	t_vec2 new_pos = (t_vec2){
		head_pos.v1 + state->direction.v1, head_pos.v2 + state->direction.v2
	};

	if (new_pos.v1 < 0)
		new_pos.v1 = GRID_WIDTH - 1;
	if (new_pos.v1 >= GRID_WIDTH)
		new_pos.v1 = 0;
	if (new_pos.v2 < 0)
		new_pos.v2 = GRID_HEIGHT - 1;
	if (new_pos.v2 >= GRID_HEIGHT)
		new_pos.v2 = 0;
	state->body[state->head] = new_pos;
}

static int16_t on_snake(t_snake_state *state, t_vec2 pos)
{
	for (int16_t i = 0; i < state->length; i++)
		if (state->body[i].v1 == pos.v1 && state->body[i].v2 == pos.v2)
			return (i);
	return (-1);
}

static int16_t on_fruit(t_snake_state *state, t_vec2 pos)
{
	for (int16_t i = 0; i < SNAKE_MAX_FRUIT; i++)
		if (
			state->fruits[i].active
			&& state->fruits[i].pos.v1 == pos.v1
			&& state->fruits[i].pos.v2 == pos.v2
		)
			return (i);
	return (-1);
}

static void update_fruits(t_snake_state *state, uint32_t elapsed_us)
{
	static uint32_t total_elapsed_us = 0;
	total_elapsed_us += elapsed_us;
	if (total_elapsed_us < SNAKE_FRUIT_SPAWN_SPEED_US)
		return;
	total_elapsed_us -= SNAKE_FRUIT_SPAWN_SPEED_US;

	for (uint16_t i = 0; i < SNAKE_MAX_FRUIT; i++)
	{
		if (state->fruits[i].active)
			continue;
		while (!state->fruits[i].active) {
			state->fruits[i].pos.v1 = random_32u() % GRID_WIDTH;
			state->fruits[i].pos.v2 = random_32u() % GRID_HEIGHT;
			if (
				on_fruit(state, state->fruits[i].pos) == -1
				&& on_snake(state, state->fruits[i].pos) == -1
			)
				state->fruits[i].active = true;
		}
		break;
 	}
}

static void update_collision(t_snake_state *state)
{
	int16_t fruit = on_fruit(state, state->body[state->head]);
	if (fruit != -1) {
		state->fruits[fruit].active = false;
	}
	if (on_snake(state, state->body[state->head]) > 0) {
		state->direction = (t_vec2){0, 0};
		state->alive = false;
	}
}

static void update_game(t_snake_state *state, uint32_t elapsed_us)
{
	if (!state->alive)
		return;

	update_buttons(state);	
	update_direction(state, elapsed_us);
	update_collision(state);
	update_fruits(state, elapsed_us);
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

	uint32_t last_frame_us = get_time_us();
	while (1) {
		uint32_t current_frame_us = get_time_us();
		uint32_t elapsed_us = current_frame_us - last_frame_us;
		last_frame_us = current_frame_us;

		update_game(&state, elapsed_us);
		draw_snake(display, &snake_display, state);

		uint32_t frame_time = get_time_us() - current_frame_us;
		if (frame_time < FRAME_US)
			usleep(FRAME_US - frame_time);
	}
}
