#include "uart.h"
#include "irq.h"
#include "mapping.h"
#include "snake.h"
#include "buttons.h"

int kmain(void)
{
	mapping_uart();
	mapping_spi();
	mapping_display();
	mapping_buttons();

	uart_init(BCM2835_UART0, UART_CLK, UART_BAUD);
	uart_printf(BCM2835_UART0, "hello world\r\n");

	irq_init();

	irq_register(IRQ_GPIO_BANK0, buttons_irq_handler, 0);
	irq_enable_line(IRQ_GPIO_BANK0);

	irq_enable();

	snake();
	return (0);
}
