#include "helpers/time.h"
#include "snake.h"
#include "buttons.h"

void snake(void)
{
	uint32_t excess;
	uint32_t start_us;
	uint32_t elapsed_us;

	excess = 0u;
	while (1) {
		start_us = get_time_us();
		if (button_left()) {
		}
		if (button_up()) {
		}
		if (button_right()) {
		}
		if (button_down()) {
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
