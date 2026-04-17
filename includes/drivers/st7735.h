#ifndef ST7735_H
#define ST7735_H

#include "display.h"
#include "drivers/spi.h"

typedef enum e_st7735_dc_mode
{
	ST7735_COMMAND = 0,
	ST7735_DATA = 1
} 	t_st7735_dc_mode;

typedef enum e_st7735_cmd
{
	ST7735_NOP      = 0x00,
	ST7735_SWRESET  = 0x01,
	ST7735_RDDID    = 0x04,
	ST7735_RDDST    = 0x09,
	ST7735_SLPIN    = 0x10,
	ST7735_SLPOUT   = 0x11,
	ST7735_PTLON    = 0x12,
	ST7735_NORON    = 0x13,
	ST7735_INVOFF   = 0x20,
	ST7735_INVON    = 0x21,
	ST7735_GAMSET   = 0x26,
	ST7735_DISPOFF  = 0x28,
	ST7735_DISPON   = 0x29,
	ST7735_CASET    = 0x2A,
	ST7735_RASET    = 0x2B,
	ST7735_RAMWR    = 0x2C,
	ST7735_RAMRD    = 0x2E,
	ST7735_PTLAR    = 0x30,
	ST7735_MADCTL   = 0x36,
	ST7735_COLMOD   = 0x3A,
	ST7735_FRMCTR1  = 0xB1,
	ST7735_FRMCTR2  = 0xB2,
	ST7735_FRMCTR3  = 0xB3,
	ST7735_INVCTR   = 0xB4,
	ST7735_DISSET5  = 0xB6,
	ST7735_PWCTR1   = 0xC0,
	ST7735_PWCTR2   = 0xC1,
	ST7735_PWCTR3   = 0xC2,
	ST7735_PWCTR4   = 0xC3,
	ST7735_PWCTR5   = 0xC4,
	ST7735_VMCTR1   = 0xC5,
	ST7735_GMCTRP1  = 0xE0,
	ST7735_GMCTRN1  = 0xE1
} 	t_st7735_cmd;

typedef enum e_st7735_madctl
{
	ST7735_MADCTL_MH  = 0x04,
	ST7735_MADCTL_BGR = 0x08,
	ST7735_MADCTL_ML  = 0x10,
	ST7735_MADCTL_MV  = 0x20,
	ST7735_MADCTL_MX  = 0x40,
	ST7735_MADCTL_MY  = 0x80
}	t_st7735_madctl;

typedef enum e_st7735_colmod
{
	ST7735_COLMOD_12BIT = 0x03,
	ST7735_COLMOD_16BIT = 0x05,
	ST7735_COLMOD_18BIT = 0x06
}	t_st7735_colmod;

typedef struct s_st7735_pins
{
	uint32_t	dc_gpio;
	uint32_t	rst_gpio;
} 	t_st7735_pins;

typedef struct s_st7735
{
	t_st7735_pins	pins;
	uint16_t		clk_div;
	t_spi_mode		spi_mode;
	uint8_t			madctl;
	t_st7735_colmod	colmod;
} 	t_st7735;

void	st7735_hw_reset(t_display *display);
void	st7735_set_window(
	t_display *display, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1
);
void	st7735_write_pixels(
	t_display *display, const uint16_t *pixels, uint32_t count
);
void	st7735_write_color(
	t_display *display, uint16_t color, uint32_t count
);
void st7735_init(t_display *display);

typedef struct s_display_fn t_display_fn;

static const t_display_fn st7735_fn = {
	.init = st7735_init,
	.reset = st7735_hw_reset,
	.set_window = st7735_set_window,
	.write_pixels = st7735_write_pixels,
	.write_color = st7735_write_color
};

#endif
