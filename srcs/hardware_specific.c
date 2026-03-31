#include "gpio.h"

extern void set_up_input_gpio(uint32_t gpio)
{
    if (gpio > GPIO_MAX)
        return;
	gpio_set_func(gpio, GPIO_INPUT);
	gpio_set_pull(gpio, GPIO_PULL_UP);
	gpio_event_clear(gpio);
	gpio_enable_falling(gpio);
	gpio_event_clear(gpio);
}

extern void set_up_uart_gpio(uint32_t gpio)
{
    if (gpio > GPIO_MAX)
        return;
	gpio_set_func(gpio, GPIO_ALT0);
	gpio_set_pull(gpio, GPIO_PULL_OFF);
}
