.section .text

.global irq_disable
.global irq_enable

.global cpu_use_low_vectors_vbar
.global cpu_set_vbar
.global cpu_isb
.global irq_vector_init

.global irq_controller_reset
.global irq_controller_enable
.global irq_controller_disable
.global irq_controller_pending_1
.global irq_controller_pending_2
.global irq_controller_basic_pending

irq_disable:
	cpsid if
	bx lr

irq_enable:
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr_c, r0
	bx lr

cpu_use_low_vectors_vbar:
	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #0x2000
	mcr p15, 0, r0, c1, c0, 0
	bx lr

cpu_set_vbar:
	mcr p15, 0, r0, c12, c0, 0
	bx lr

cpu_isb:
	mov r0, #0
	mcr p15, 0, r0, c7, c5, 4
	bx lr

irq_vector_init:
	bl cpu_use_low_vectors_vbar
	ldr r0, =__exception_vectors
	bl cpu_set_vbar
	bl cpu_isb
	bx lr

irq_controller_reset:
	ldr r0, =0x2000b21c
	ldr r1, =0xffffffff
	str r1, [r0]

	ldr r0, =0x2000b220
	str r1, [r0]

	ldr r0, =0x2000b224
	str r1, [r0]

	ldr r0, =0x2000b20c
	mov r1, #0
	str r1, [r0]

	bx lr

irq_controller_enable:
	/* r0 = irq number */

	cmp r0, #32
	blt irq_enable_1

	cmp r0, #64
	blt irq_enable_2

	cmp r0, #72
	bhs irq_ctrl_ret

	b irq_enable_basic

irq_enable_1:
	ldr r1, =0x2000b210
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

irq_enable_2:
	sub r0, r0, #32
	ldr r1, =0x2000b214
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

irq_enable_basic:
	sub r0, r0, #64
	ldr r1, =0x2000b218
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

irq_controller_disable:
	/* r0 = irq number */

	cmp r0, #32
	blt irq_disable_1

	cmp r0, #64
	blt irq_disable_2

	cmp r0, #72
	bhs irq_ctrl_ret

	b irq_disable_basic

irq_disable_1:
	ldr r1, =0x2000b21c
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

irq_disable_2:
	sub r0, r0, #32
	ldr r1, =0x2000b220
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

irq_disable_basic:
	sub r0, r0, #64
	ldr r1, =0x2000b224
	mov r2, #1
	lsl r2, r2, r0
	str r2, [r1]
	bx lr

irq_controller_pending_1:
	ldr r0, =0x2000b204
	ldr r0, [r0]
	bx lr

irq_controller_pending_2:
	ldr r0, =0x2000b208
	ldr r0, [r0]
	bx lr

irq_controller_basic_pending:
	ldr r0, =0x2000b200
	ldr r0, [r0]
	bx lr

irq_ctrl_ret:
	bx lr
