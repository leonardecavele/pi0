#include "drivers/uart.h"
#include "drivers/irq.h"
#include "drivers/spi.h"
#include "drivers/st7735.h"
#include "system/mapping.h"
#include "system/buttons.h"
#include "games/snake.h"
#include "display/display.h"

int kmain(void)
{
	mapping_uart();
	mapping_spi();
	mapping_display();
	mapping_buttons();

	uart_init(BCM2835_UART0, UART_CLK, UART_BAUD);
	uart_printf(BCM2835_UART0, "UART OK\r\n");

	uart_printf(BCM2835_UART0, "setting up IRQ\r\n");
	init_irq();
	register_irq(IRQ_GPIO_BANK0, buttons_irq_handler, 0);
	enable_line_irq(IRQ_GPIO_BANK0);
	enable_irq();
	uart_printf(BCM2835_UART0, "IRQ set up\r\n");

	uart_printf(BCM2835_UART0, "setting up DISPLAY\r\n");
	t_st7735 st7735 = {
		.pins = {
			.dc_gpio = DISPLAY_DC_GPIO,
			.rst_gpio = DISPLAY_RST_GPIO
		},
		.clk_div = 64u,
		.spi_mode = SPI_MODE0,
		.madctl = 0u,
		.colmod = ST7735_COLMOD_16BIT
	};
	t_display display = {
		.width = 128u,
		.height = 160u,
		.driver = ((void *)&st7735),
		.fn = ((void *)&st7735_fn)
	};
	display_init(&display);
	uart_printf(BCM2835_UART0, "DISPLAY set up\r\n");

	#include "display/draw.h"
	while (1) {
		draw_clear(&display, 0xFFFFu);
		msleep(1000);
		draw_fill_square(&display, 10u, 10u, 30u, 0xF800u);
		msleep(1000);
		draw_fill_rect(&display, 50u, 20u, 40u, 25u, 0x07E0u);
		msleep(1000);
		draw_rect(&display, 5u, 5u, 118u, 150u, 0x0000u);
		msleep(1000);
		draw_circle(&display, 64, 80, 20, 0x001Fu);
		msleep(1000);
	}

	snake();
	return (0);
}
