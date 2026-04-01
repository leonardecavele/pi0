#include "drivers/uart.h"
#include "drivers/irq.h"
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

	init_irq();

	register_irq(IRQ_GPIO_BANK0, buttons_irq_handler, 0);
	enable_line_irq(IRQ_GPIO_BANK0);

	enable_irq();

	snake();
	return (0);
}
