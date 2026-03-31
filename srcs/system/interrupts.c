#include "gpio.h"
#include "mapping.h"

extern volatile bool g_left_button = false;
extern volatile bool g_up_button = false;
extern volatile bool g_right_button = false;
extern volatile bool g_down_button = false;

extern void handle_irq(void)
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
