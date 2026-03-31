#include "gpio.h"
#include "uart.h"
#include "irq.h"
#include "mapping.h"
#include "snake.h"

int kmain(void)
{
	mapping_uart();
	mapping_buttons();
	mapping_spi();
	mapping_display();

	uart_init(BCM2835_UART0, UART_CLK, UART_BAUD);
	uart_printf(BCM2835_UART0, "hello world\r\n");

	irq_controller_reset();
	irq_controller_enable(IRQ_GPIO_BANK0);
	irq_enable();
	
	snake();
	return 0;
}
