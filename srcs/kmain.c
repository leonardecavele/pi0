#include "drivers/uart.h"
#include "drivers/irq.h"
#include "mapping.h"
#include "snake.h"
#include "buttons.h"

#include "drivers/spi.h"
#include "drivers/st7735.h"
#include "display.h"
#include "draw.h"

int kmain(void)
{
	mapping_uart();
	mapping_spi();
	mapping_display();
	mapping_buttons();

	uart_init(BCM2835_UART0, UART_CLK, UART_BAUD);
	uart_printf(BCM2835_UART0, "UART set up\r\n");

	uart_printf(BCM2835_UART0, "setting up IRQ\r\n");
	init_irq();
	register_irq(IRQ_GPIO_BANK0, buttons_irq_handler, 0);
	enable_line_irq(IRQ_GPIO_BANK0);
	enable_irq();
	uart_printf(BCM2835_UART0, "IRQ set up\r\n");

	t_display display;
	t_st7735 st7735;

	st7735_init_struct(&st7735, 128u, 160u, 0u, 0u);
	st7735_attach_display(&display, &st7735);

	if (display_init(&display) == false) {
		uart_printf(BCM2835_UART0, "display init failed\r\n");
		while (1) {}
	}
	uart_printf(BCM2835_UART0, "display ok\r\n");

	draw_clear(&display, 0x0000u);
	draw_fill_square(&display, 10u, 10u, 30u, 0xF800u);
	draw_fill_rect(&display, 50u, 20u, 40u, 25u, 0x07E0u);
	draw_rect(&display, 5u, 5u, 118u, 150u, 0xFFFFu);
	draw_circle(&display, 64, 80, 20, 0x001Fu);

	snake();
	return (0);
}
