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

void display_reset(void);
void display_set_mode(t_display_mode mode);

#endif
