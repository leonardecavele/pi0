#include "buttons.h"
#include "gpio.h"
#include "irq.h"
#include "mapping.h"

static volatile bool g_left_button = false;
static volatile bool g_up_button = false;
static volatile bool g_right_button = false;
static volatile bool g_down_button = false;

void buttons_irq_handler(void *ctx)
{
	(void)ctx;
	if (gpio_event_pending(LEFT_BUTTON_GPIO))
	{
		gpio_event_clear(LEFT_BUTTON_GPIO);
		g_left_button = true;
	}
	if (gpio_event_pending(UP_BUTTON_GPIO))
	{
		gpio_event_clear(UP_BUTTON_GPIO);
		g_up_button = true;
	}
	if (gpio_event_pending(RIGHT_BUTTON_GPIO))
	{
		gpio_event_clear(RIGHT_BUTTON_GPIO);
		g_right_button = true;
	}
	if (gpio_event_pending(DOWN_BUTTON_GPIO))
	{
		gpio_event_clear(DOWN_BUTTON_GPIO);
		g_down_button = true;
	}
}

bool button_left(void)
{
	bool value = g_left_button;
	g_left_button = false;	
	return value;
}

bool button_up(void)
{
	bool value = g_up_button;
	g_up_button = false;	
	return value;
}

bool button_right(void)
{
	bool value = g_right_button;
	g_right_button = false;	
	return value;
}

bool button_down(void)
{
	bool value = g_down_button;
	g_down_button = false;	
	return value;
}
