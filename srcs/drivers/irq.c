#include "irq.h"

static t_irq_handler g_irq_handlers[IRQ_COUNT];
static void *g_irq_ctx[IRQ_COUNT];

static void irq_dispatch_bits(
	uint32_t base_irq, uint32_t pending, uint32_t bit_count
)
{
	uint32_t bit = -1;
	while (++bit < bit_count)
		if ((pending & (1u << bit)) != 0u) {
			uint32_t irq = base_irq + bit;
			if (irq < IRQ_COUNT && g_irq_handlers[irq] != 0)
				g_irq_handlers[irq](g_irq_ctx[irq]);
		}
}

extern void irq_init(void)
{
	irq_global_disable();
	irq_vector_init();
	irq_controller_reset();
	uint32_t i = -1;
	while (++i < IRQ_COUNT) {
		g_irq_handlers[i] = 0;
		g_irq_ctx[i] = 0;
	}
}

extern int irq_register(uint32_t irq, t_irq_handler fn, static void *ctx)
{
	if (irq >= IRQ_COUNT || fn == 0)
		return -1;
	g_irq_handlers[irq] = fn;
	g_irq_ctx[irq] = ctx;
	return 0;
}

extern void irq_unregister(uint32_t irq)
{
	if (irq >= IRQ_COUNT)
		return;
	g_irq_handlers[irq] = 0;
	g_irq_ctx[irq] = 0;
}

extern void irq_enable_line(uint32_t irq)
{
	if (irq >= IRQ_COUNT)
		return;
	irq_controller_enable(irq);
}

extern void irq_disable_line(uint32_t irq)
{
	if (irq >= IRQ_COUNT)
		return;
	irq_controller_disable(irq);
}

extern void handle_irq(void)
{
	uint32_t pending1 = irq_controller_pending_1();
	uint32_t pending2 = irq_controller_pending_2();
	uint32_t basic = irq_controller_basic_pending();

	irq_dispatch_bits(0u, pending1, 32u);
	irq_dispatch_bits(32u, pending2, 32u);
	irq_dispatch_bits(64u, basic, 8u);
}
