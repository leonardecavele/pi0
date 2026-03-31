.extern _start
.extern handle_irq

.section .text
.global __exception_vectors

.align 5
__exception_vectors:
	b _start    // reset
	b .         // undefined instruction
	b .         // swi / svc
	b .         // prefetch abort
	b .         // data abort
	b .         // reserved
	b irq		// irq
	b .         // fiq

irq:
    stmfd sp!, {r0-r3, r12, lr}
    bl handle_irq
    ldmfd sp!, {r0-r3, r12, lr}
    subs pc, lr, #4
