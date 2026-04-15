#include "helpers/time.h"
#include "display.h"
#include "mapping.h"

void display_reset(void)
{
	gpio_write(DISPLAY_RST_GPIO, true);
	usleep(5000u);
	gpio_write(DISPLAY_RST_GPIO, false);
	usleep(5000u);
	gpio_write(DISPLAY_RST_GPIO, true);
	usleep(5000u);
}

void display_set_mode(t_display_mode mode)
{
	if (mode == DISPLAY_COMMAND)
		gpio_write(DISPLAY_DC_GPIO, false);
	else
		gpio_write(DISPLAY_DC_GPIO, true);
}

/* build a structure screen with height and size so functions can
   adapt by itself according to the screen
*/

/* to do */
void cursed_square(void)
{
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
}
