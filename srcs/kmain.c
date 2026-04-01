#include "drivers/uart.h"
#include "drivers/irq.h"
#include "mapping.h"
#include "snake.h"
#include "buttons.h"

#include "drivers/spi.h"
#include "display.h"

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


	spi_init(64u, SPI_MODE0);
	display_reset();

	display_set_mode(DISPLAY_COMMAND);
	spi_begin();
	spi_write(0x01);
	spi_end();

	display_set_mode(DISPLAY_COMMAND);
	spi_begin();
	spi_write(0x11);
	spi_end();
	usleep(150000u);

	display_set_mode(DISPLAY_COMMAND);
	spi_begin();
	spi_write(0x3A);
	spi_end();

	display_set_mode(DISPLAY_BYTES);
	spi_begin();
	spi_write(0x05);
	spi_end();

	display_set_mode(DISPLAY_COMMAND);
	spi_begin();
	spi_write(0x36);
	spi_end();

	display_set_mode(DISPLAY_BYTES);
	spi_begin();
	spi_write(0x00);
	spi_end();

	display_set_mode(DISPLAY_COMMAND);
	spi_begin();
	spi_write(0x29);
	spi_end();
	usleep(20000u);

	display_set_mode(DISPLAY_COMMAND);
	spi_begin();
	spi_write(0x2A);
	spi_end();

	display_set_mode(DISPLAY_BYTES);
	spi_begin();
	spi_write(0x00);
	spi_write(0x00);
	spi_write(0x00);
	spi_write(127);
	spi_end();

	display_set_mode(DISPLAY_COMMAND);
	spi_begin();
	spi_write(0x2B);
	spi_end();

	display_set_mode(DISPLAY_BYTES);
	spi_begin();
	spi_write(0x00);
	spi_write(0x00);
	spi_write(0x00);
	spi_write(127);
	spi_end();

	display_set_mode(DISPLAY_COMMAND);
	spi_begin();
	spi_write(0x2C);
	spi_end();

	display_set_mode(DISPLAY_BYTES);
	spi_begin();
	for (uint32_t i = 0; i < 128u * 128u; ++i)
	{
		spi_write(0xF8);
		spi_write(0x00);
	}
	spi_end();

	snake();
	return (0);
}
