#ifndef BUTTONS_H
#define BUTTONS_H

#include "standard.h"

void buttons_irq_handler(void *ctx);

bool button_left(void);
bool button_up(void);
bool button_right(void);
bool button_down(void);

#endif
