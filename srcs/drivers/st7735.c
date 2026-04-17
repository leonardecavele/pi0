#include "helpers/time.h"
#include "drivers/gpio.h"
#include "drivers/st7735.h"

static void	st7735_set_mode(t_st7735 *st7735, t_st7735_dc_mode mode)
{
	gpio_write(st7735->pins.dc_gpio, mode == ST7735_DATA);
}

static void	st7735_write_command(t_st7735 *st7735, uint8_t cmd)
{
	st7735_set_mode(st7735, ST7735_COMMAND);
	spi_begin();
	spi_write(cmd);
	spi_end();
}

static void	st7735_write_data8(t_st7735 *st7735, uint8_t value)
{
	st7735_set_mode(st7735, ST7735_DATA);
	spi_begin();
	spi_write(value);
	spi_end();
}

static void	st7735_write_data16_pair(
	t_st7735 *st7735, uint16_t first, uint16_t second
)
{
	st7735_set_mode(st7735, ST7735_DATA);
	spi_begin();
	spi_write((uint8_t)(first >> 8));
	spi_write((uint8_t)(first & 0xffu));
	spi_write((uint8_t)(second >> 8));
	spi_write((uint8_t)(second & 0xffu));
	spi_end();
}

extern void	st7735_hw_reset(t_display *display)
{
	t_st7735	*st7735;

	st7735 = (t_st7735 *)display->driver;
	gpio_write(st7735->pins.rst_gpio, true);
	usleep(5000u);
	gpio_write(st7735->pins.rst_gpio, false);
	usleep(5000u);
	gpio_write(st7735->pins.rst_gpio, true);
	usleep(5000u);
}

extern void	st7735_set_window(
	t_display *display, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1
)
{
	t_st7735	*st7735;
	uint16_t	start;
	uint16_t	end;

	st7735 = (t_st7735 *)display->driver;
	start = (uint16_t)(x0 + display->x_offset);
	end = (uint16_t)(x1 + display->x_offset);
	st7735_write_command(st7735, ST7735_CASET);
	st7735_write_data16_pair(st7735, start, end);
	start = (uint16_t)(y0 + display->y_offset);
	end = (uint16_t)(y1 + display->y_offset);
	st7735_write_command(st7735, ST7735_RASET);
	st7735_write_data16_pair(st7735, start, end);
	st7735_write_command(st7735, ST7735_RAMWR);
}

extern void	st7735_write_pixels(
	t_display *display, const uint16_t *pixels, uint32_t count
)
{
	t_st7735	*st7735;
	uint32_t	i;

	if (pixels == 0)
		return ;
	st7735 = (t_st7735 *)display->driver;
	st7735_set_mode(st7735, ST7735_DATA);
	spi_begin();
	i = 0u;
	while (i < count)
	{
		spi_write((uint8_t)(pixels[i] >> 8));
		spi_write((uint8_t)(pixels[i] & 0xffu));
		++i;
	}
	spi_end();
}

extern void	st7735_write_color(
	t_display *display, uint16_t color, uint32_t count
)
{
	t_st7735	*st7735;
	uint32_t	i;

	st7735 = (t_st7735 *)display->driver;
	st7735_set_mode(st7735, ST7735_DATA);
	spi_begin();
	i = 0u;
	while (i < count)
	{
		spi_write((uint8_t)(color >> 8));
		spi_write((uint8_t)(color & 0xffu));
		++i;
	}
	spi_end();
}

extern void st7735_init(t_display *display)
{
	t_st7735	*st7735;

	st7735 = (t_st7735 *)display->driver;
	spi_init(st7735->clk_div, st7735->spi_mode);
	st7735_hw_reset(display);
	st7735_write_command(st7735, ST7735_SWRESET);
	usleep(150000u);
	st7735_write_command(st7735, ST7735_SLPOUT);
	usleep(150000u);
	st7735_write_command(st7735, ST7735_COLMOD);
	st7735_write_data8(st7735, (uint8_t)st7735->colmod);
	st7735_write_command(st7735, ST7735_MADCTL);
	st7735_write_data8(st7735, st7735->madctl);
	st7735_write_command(st7735, ST7735_NORON);
	usleep(10000u);
	st7735_write_command(st7735, ST7735_DISPON);
	usleep(20000u);
	st7735_set_window(
		display, 0u, 0u,
		(uint16_t)(display->width - 1u),
		(uint16_t)(display->height - 1u)
	);
}
