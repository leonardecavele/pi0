#include "helpers/time.h"
#include "games/snake/snake.h"
#include "system/buttons.h"
#include "display/display.h"
#include "display/draw.h"

#include "drivers/uart.h"
void snake(t_display *display)
{
	uint32_t excess;
	uint32_t start_us;
	uint32_t elapsed_us;

	bool button_left_status = false;
	bool button_up_status = false;
	bool button_right_status = false;
	bool button_down_status = false;

	draw_clear(display, 0xFFFFu);
	excess = 0u;
	while (1) {
		start_us = get_time_us();
		if (button_left()) {
			button_left_status = !button_left_status;
			if (button_left_status)
				draw_fill_square(display, 10u, 10u, 30u, 0xF800u);
			else
				draw_fill_square(display, 10u, 10u, 30u, 0xFFFFu);
		}
		if (button_up()) {
			button_up_status = !button_up_status;
			if (button_up_status)
				draw_fill_rect(display, 50u, 20u, 40u, 25u, 0x07E0u);
			else
				draw_fill_rect(display, 50u, 20u, 40u, 25u, 0xFFFFu);
		}
		if (button_right()) {
			button_right_status = !button_right_status;
			if (button_right_status)
				draw_rect(display, 5u, 5u, 118u, 150u, 0x0000u);
			else
				draw_rect(display, 5u, 5u, 118u, 150u, 0xFFFFu);
		}
		if (button_down()) {
			button_down_status = !button_down_status;
			if (button_down_status)
				draw_circle(display, 64, 80, 20, 0x001Fu);
			else
				draw_circle(display, 64, 80, 20, 0xFFFFu);
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
