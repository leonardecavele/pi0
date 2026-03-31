#include "uart.h"
#include "time.h"
#include "snake.h"
#include "irq.h"

/* not clean yet */
extern void snake(void)
{
	/* main loop */
	uint32_t excess = 0u;
	while (1) {
		uint32_t start_us = get_time_us();

		if (g_left_button) {
			g_left_button = false;
		}
		if (g_up_button) {
			g_up_button = false;
		}
		if (g_right_button) {
			g_right_button = false;
		}
		if (g_down_button) {
			g_down_button = false;
		}

		uint32_t elapsed_us = (get_time_us() - start_us) + excess;

		//uart_printf(
		//	BCM2835_UART0,
		//	"now=%u us | frame=%u us | excess=%u\r\n",
		//	get_time_us(), elapsed_us, excess
		//);

		if (elapsed_us < FRAME_US) {
			usleep(FRAME_US - elapsed_us);
			excess = 0u;
		}
		else
			excess = elapsed_us - FRAME_US;
	}
}
