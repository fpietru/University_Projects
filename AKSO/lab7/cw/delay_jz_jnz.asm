section .text

global delay

delay:
	; liczba cykli przed
	rdtsc
	shl rdx, 32
	or rax, rdx
  mov rcx, rax ; rcx - timestamp przed
  test rdi, rdi
  jz .end

.loop:
	dec rdi
	jnz .loop

.end:
	; liczba cykli po
	rdtsc
	shl rdx, 32
	or rax, rdx ; rax - timestamp po
	sub rax, rcx ; roznica (po - przed) zapisana w rax
	ret