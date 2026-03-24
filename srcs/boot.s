.section .text
.global _start

_start:
	/* disable interrupts */
	cpsid if

	/* temporary stack */
	ldr r0, =__stack_top
	mov sp, r0

	ldr r0, =__bss_start
	ldr r1, =__bss_end
	mov r2, #0

bss_loop:
	/* write 0 then increase pointer by 1 while in bss */
	cmp r0, r1
	bhs bss_done
	strb r2, [r0], #1
	b bss_loop

bss_done:
	/* branch to kernel main */
	bl kmain

cpu_hang:
	b cpu_hang
