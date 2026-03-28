#include "gpio.h"

/* WIP before real timer set-up */
static void gpio_delay(uint32_t n)
{
	volatile uint32_t	i;

	i = 0u;
	while (i < n)
		i++;
}

void gpio_set_func(uint32_t gpio, t_gpio_funcsel func)
{
	uint32_t	reg;
	uint32_t	shift;
	uint32_t	mask;
	uint32_t	val;

	if (gpio > GPIO_MAX)
		return ;
	reg = REG4B(GPIO_FSEL(gpio));
	shift = GPIO_FSEL_SHIFT(gpio);
	mask = 0x7u << shift;
	val = ((uint32_t)func << shift);
	reg &= ~mask;
	reg |= val;
	REG4B(GPIO_FSEL(gpio)) = reg;
}

void gpio_write(uint32_t gpio, bool value)
{
	if (gpio > GPIO_MAX)
		return ;
	if (value)
		REG4B(GPIO_SET(gpio)) = GPIO_MASK(gpio);
	else
		REG4B(GPIO_CLR(gpio)) = GPIO_MASK(gpio);
}

bool gpio_read(uint32_t gpio)
{
	if (gpio > GPIO_MAX)
		return (false);
	return (GPIO_GET_BIT(gpio) != 0u);
}

void gpio_set_pull(uint32_t gpio, t_gpio_pull pull)
{
	if (gpio > GPIO_MAX)
		return ;
	REG4B(BCM2835_GPIO + GPPUD) = ((uint32_t)pull << PUD_SHIFT) & PUD_MASK;
	gpio_delay(150u);
	REG4B(GPIO_PUDCLK(gpio)) = GPIO_MASK(gpio);
	gpio_delay(150u);
	REG4B(BCM2835_GPIO + GPPUD) = 0u;
	REG4B(GPIO_PUDCLK(gpio)) = 0u;
}
