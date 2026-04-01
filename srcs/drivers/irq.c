#include "drivers/irq.h"

static t_irq_handler g_irq_handlers[IRQ_COUNT];
static void *g_irq_ctx[IRQ_COUNT];

static void dispatch_bits_irq(
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

#include "drivers/uart.h"
extern void init_irq(void)
{
	uart_printf(BCM2835_UART0, "A\r\n");
	vector_init_irq();
	uart_printf(BCM2835_UART0, "B\r\n");
	controller_reset_irq();
	uart_printf(BCM2835_UART0, "C\r\n");
	uint32_t i = -1;
	while (++i < IRQ_COUNT) {
		g_irq_handlers[i] = 0;
		g_irq_ctx[i] = 0;
	}
	uart_printf(BCM2835_UART0, "D\r\n");
}

extern int register_irq(uint32_t irq, t_irq_handler fn, void *ctx)
{
	if (irq >= IRQ_COUNT || fn == 0)
		return -1;
	g_irq_handlers[irq] = fn;
	g_irq_ctx[irq] = ctx;
	return 0;
}

extern void unregister_irq(uint32_t irq)
{
	if (irq >= IRQ_COUNT)
		return;
	g_irq_handlers[irq] = 0;
	g_irq_ctx[irq] = 0;
}

extern void enable_line_irq(uint32_t irq)
{
	if (irq >= IRQ_COUNT)
		return;
	controller_enable_irq(irq);
}

extern void disable_line_irq(uint32_t irq)
{
	if (irq >= IRQ_COUNT)
		return;
	controller_disable_irq(irq);
}

extern void handle_irq(void)
{
	uint32_t pending1 = controller_pending_1_irq();
	uint32_t pending2 = controller_pending_2_irq();
	uint32_t basic = controller_basic_pending_irq();

	dispatch_bits_irq(0u, pending1, 32u);
	dispatch_bits_irq(32u, pending2, 32u);
	dispatch_bits_irq(64u, basic, 8u);
}
