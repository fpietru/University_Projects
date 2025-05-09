section .text

global mean

mean:
	mov rax, rdi
	add rax, rsi
	rcr rax, 1
	ret