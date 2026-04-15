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

typedef struct s_st7735
{
	uint16_t	width;
	uint16_t	height;
	uint16_t	x_offset;
	uint16_t	y_offset;
	uint16_t	clk_div;
	t_spi_mode	spi_mode;
	uint8_t		madctl;
	uint8_t		colmod;
} 	t_st7735;

void	st7735_init_struct(t_st7735 *st7735, uint16_t width, uint16_t height,
		uint16_t x_offset, uint16_t y_offset);
void	st7735_attach_display(t_display *display, t_st7735 *st7735);

#endif
