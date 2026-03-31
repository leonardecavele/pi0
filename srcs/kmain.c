#include "gpio.h"
#include "uart.h"
#include "command.h"
#include "irq.h"
#include "time.h"
#include "hardware_specific.h"

#define TARGET_FPS 1u
#define FRAME_US (1000000u / TARGET_FPS)

static volatile bool g_left_button = false;
static volatile bool g_up_button = false;
static volatile bool g_right_button = false;
static volatile bool g_down_button = false;

void handle_irq(void)
{
	if (gpio_event_pending(LEFT_BUTTON_GPIO)) {
		gpio_event_clear(LEFT_BUTTON_GPIO);
		g_left_button = true;
	}
	if (gpio_event_pending(UP_BUTTON_GPIO)) {
		gpio_event_clear(UP_BUTTON_GPIO);
		g_up_button = true;
	}
	if (gpio_event_pending(RIGHT_BUTTON_GPIO)) {
		gpio_event_clear(RIGHT_BUTTON_GPIO);
		g_right_button = true;
	}
	if (gpio_event_pending(DOWN_BUTTON_GPIO)) {
		gpio_event_clear(DOWN_BUTTON_GPIO);
		g_down_button = true;
	}
}

int kmain(void)
{
	/* init UART0 */
	set_up_uart_gpio(UART_TXD_GPIO);
	set_up_uart_gpio(UART_RXD_GPIO);
	uart_init(BCM2835_UART0, UART_CLK, UART_BAUD);
	uart_printf(BCM2835_UART0, "hello world\r\n");

	set_up_input_gpio(LEFT_BUTTON_GPIO);
	set_up_input_gpio(UP_BUTTON_GPIO);
	set_up_input_gpio(RIGHT_BUTTON_GPIO);
	set_up_input_gpio(DOWN_BUTTON_GPIO);

	irq_controller_reset();
	irq_controller_enable(IRQ_GPIO_BANK0);
	irq_enable();

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
