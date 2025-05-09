section .text

global delay

delay:

	; liczba cykli przed
	rdtsc
	shl rdx, 32
	or rax, rdx
  mov rsi, rax ; rsi - timestamp przed  
  mov rcx, rdi
  jrcxz .end

.loop:
	loop .loop

.end:
	; liczba cykli po
	rdtsc
	shl rdx, 32
	or rax, rdx ; rax - timestamp po
	sub rax, rsi ; roznica (po - przed) zapisana w rax
	ret