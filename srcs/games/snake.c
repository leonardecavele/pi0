#include "helpers/time.h"
#include "games/snake.h"
#include "system/buttons.h"
#include "display/display.h"
#include "display/draw.h"

void snake(t_display *display)
{
	uint32_t excess;
	uint32_t start_us;
	uint32_t elapsed_us;

	draw_clear(&display, 0xFFFFu);
	excess = 0u;
	while (1) {
		start_us = get_time_us();
		if (button_left()) {
			draw_fill_square(display, 10u, 10u, 30u, 0xF800u);
		}
		if (button_up()) {
			draw_fill_rect(display, 50u, 20u, 40u, 25u, 0x07E0u);
		}
		if (button_right()) {
			draw_rect(display, 5u, 5u, 118u, 150u, 0x0000u);
		}
		if (button_down()) {
			draw_circle(display, 64, 80, 20, 0x001Fu);
		}
		elapsed_us = (get_time_us() - start_us) + excess;
		if (elapsed_us < FRAME_US) {
			usleep(FRAME_US - elapsed_us);
			excess = 0u;
		}
		else
			excess = elapsed_us - FRAME_US;
	}
}
