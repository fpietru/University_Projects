global hello
extern putchar

section .rodata
	hello_text: db `Hello World!\n\0`

section .text

hello:
	push rbx
	lea rbx, [rel hello_text]

.loop:
	movzx edi, byte [rbx]
	test edi, edi
	jz .break_loop
	call putchar wrt ..plt
	inc rbx
	jmp .loop

.break_loop:
	pop rbx
	ret
