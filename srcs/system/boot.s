.extern disable_irq

.section .text
.global _start

_start:
	bl disable_irq

	/* switch to IRQ mode */
	mrs r0, cpsr
	bic r0, r0, #0x1f
	orr r0, r0, #0x12
	msr cpsr_c, r0

	/* set IRQ stack */
	ldr sp, =__irq_stack_top

	/* switch to SVC mode */
	mrs r0, cpsr
	bic r0, r0, #0x1f
	orr r0, r0, #0x13
	msr cpsr_c, r0

	/* set SVC stack */
	ldr sp, =__stack_top

	/* clear .bss */
	ldr r0, =__bss_start
	ldr r1, =__bss_end
	mov r2, #0

bss_loop:
	cmp r0, r1
	bhs bss_done
	strb r2, [r0], #1
	b bss_loop

bss_done:
	/* branch to kernel main */
	bl kmain

cpu_hang:
	b cpu_hang
