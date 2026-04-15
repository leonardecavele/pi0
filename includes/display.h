#ifndef DISPLAY_H
#define DISPLAY_H

#include "helpers/standard.h"
#include "drivers/gpio.h"
#include "drivers/spi.h"

typedef enum e_display_mode
{
	DISPLAY_COMMAND = 0,
	DISPLAY_BYTES = 1
}	t_display_mode;

typedef enum e_display_cmd
{
	DISPLAY_CMD_NOP      = 0x00, /* do nothing */
	DISPLAY_CMD_SWRESET  = 0x01, /* software reset */
	DISPLAY_CMD_RDDID    = 0x04, /* read display ID */
	DISPLAY_CMD_RDDST    = 0x09, /* read display status */

	DISPLAY_CMD_SLPIN    = 0x10, /* enter sleep mode */
	DISPLAY_CMD_SLPOUT   = 0x11, /* leave sleep mode */
	DISPLAY_CMD_PTLON    = 0x12, /* enable partial mode */
	DISPLAY_CMD_NORON    = 0x13, /* return to normal display mode */

	DISPLAY_CMD_INVOFF   = 0x20, /* disable color inversion */
	DISPLAY_CMD_INVON    = 0x21, /* enable color inversion */
	DISPLAY_CMD_GAMSET   = 0x26, /* set gamma curve */
	DISPLAY_CMD_DISPOFF  = 0x28, /* turn display off */
	DISPLAY_CMD_DISPON   = 0x29, /* turn display on */

	DISPLAY_CMD_CASET    = 0x2A, /* set column range */
	DISPLAY_CMD_RASET    = 0x2B, /* set row range */
	DISPLAY_CMD_RAMWR    = 0x2C, /* write pixels to display RAM */
	DISPLAY_CMD_RAMRD    = 0x2E, /* read pixels from display RAM */

	DISPLAY_CMD_PTLAR    = 0x30, /* set partial area */
	DISPLAY_CMD_MADCTL   = 0x36, /* set orientation and RGB/BGR order */
	DISPLAY_CMD_COLMOD   = 0x3A, /* set pixel format */

	DISPLAY_CMD_FRMCTR1  = 0xB1, /* frame rate control 1 */
	DISPLAY_CMD_FRMCTR2  = 0xB2, /* frame rate control 2 */
	DISPLAY_CMD_FRMCTR3  = 0xB3, /* frame rate control 3 */
	DISPLAY_CMD_INVCTR   = 0xB4, /* inversion control */
	DISPLAY_CMD_DISSET5  = 0xB6, /* display function control */

	DISPLAY_CMD_PWCTR1   = 0xC0, /* power control 1 */
	DISPLAY_CMD_PWCTR2   = 0xC1, /* power control 2 */
	DISPLAY_CMD_PWCTR3   = 0xC2, /* power control 3 */
	DISPLAY_CMD_PWCTR4   = 0xC3, /* power control 4 */
	DISPLAY_CMD_PWCTR5   = 0xC4, /* power control 5 */
	DISPLAY_CMD_VMCTR1   = 0xC5, /* VCOM control 1 */

	DISPLAY_CMD_GMCTRP1  = 0xE0, /* positive gamma correction */
	DISPLAY_CMD_GMCTRN1  = 0xE1  /* negative gamma correction */
}	t_display_cmd;

void	display_reset(void);
void	display_set_mode(t_display_mode mode);

#endif
