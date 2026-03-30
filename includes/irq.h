#ifndef IRQ_H
#define IRQ_H

#include "standard.h"
#include "bcm2835.h"

#define IRQ_GPIO_BANK0 49u
#define IRQ_GPIO_BANK0_BIT (1u << (IRQ_GPIO_BANK0 - 32u))

typedef enum e_irq_reg
{
	IRQ_BASIC_PENDING = 0x200u,
	IRQ_PENDING_1     = 0x204u,
	IRQ_PENDING_2     = 0x208u,
	IRQ_FIQ_CTRL      = 0x20cu,
	IRQ_ENABLE_1      = 0x210u,
	IRQ_ENABLE_2      = 0x214u,
	IRQ_ENABLE_BASIC  = 0x218u,
	IRQ_DISABLE_1     = 0x21cu,
	IRQ_DISABLE_2     = 0x220u,
	IRQ_DISABLE_BASIC = 0x224u
} t_irq_reg;

void irq_init_button(void);
void irq_handler_c(void);
void irq_enable(void);
void wait_for_interrupt(void);

#endif
