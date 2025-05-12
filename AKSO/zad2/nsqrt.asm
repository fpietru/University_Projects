section .bss
	align 8
	T: resq 8192

section .text
global nsqrt

; Argumenty:
; rdi - wskaznik do tablicy Q
; rsi - wskaznik do tablicy X
; rdx - wartosc n

; Rejestry
; rbx - adres tablicy T
; r8 - s := dlugosc tablicy Q
; r9 - ss := dlugosc tablicy X, T
; r10 - i := iterator
; r11 - j := iterator
; r12 - k := zmienna lokalna
; r13 - l := zmienna lokalna
; r14 - r := zmienna lokalna
; r15 - x := zmienna lokalna


nsqrt:
	push rbx
	push r12
	push r13
	push r14
	push r15

	mov r8, rdx ; r8 - s := dlugosc tablicy Q
	shr r8, 6 ; s = n / 64 = n >> 6
	lea r9, [r8 + r8] ; r9 - ss = 2 * s := dlugosc tablicy X, T
	lea rbx, [rel T] ; rbx := adres tablicy T

	; czyszczenie Q
	mov r10, 0 ; r10 - i = 0
.clean_Q_loop: ; for (i=0; i<s; i++)
	mov qword [rdi + r10 * 8], 0 ; Q[i] = 0
	inc r10
	cmp r10, r8
	jb .clean_Q_loop

	; iteracyjnie wyliczanie Q
	mov r11, 1 ; r11 - j = 1
.main_loop: ; for (j=1; j<=n; j++)
	; czyszczenie T
	mov r10, 0 ; r10 - i = 0
.clean_T_loop: ; for (i=0; i<ss; i++)
	mov qword [rbx + r10 * 8], 0 ; T[i] = 0
	inc r10
	cmp r10, r9
    jb .clean_T_loop

.r_shift: ; T += 2^(n-j+1)*Q
	; r12 - k := n-j+1
	mov r12, rdx ; k = n
	sub r12, r11 ; k -= j
	add r12, 1   ; k += 1

	; r13 - l := k / 64 = k >> 6
	mov r13, r12 ; l = k
	shr r13, 6   ; l >>= 6

	; r14 - r := k % 6 = k & 63
	mov r14, r12 ; r = k
	and r14, 63  ; r &= 63

	; i = s-1
	mov r10, r8
	dec r10
.r_shift_loop:
	; r15 - x := Q[i]
	mov r15, qword [rdi + r10*8]

	; T[i+l] = x << r
	mov rax, r15
	mov cl, r14b
	shl rax, cl
	lea rcx, [r10 + r13]
	mov qword [rbx + rcx*8], rax

	; if (r != 0 && i+l+1 < ss)
	test r14, r14
	jz .skip

	; rax - i+l+1
	mov rax, r10
	add rax, r13
	inc rax
	cmp rax, r9
	jae .skip

	; T[i+l+1] |= Q[i] >> (64 - r)
	mov rax, r15
	mov cl, 64
	sub cl, r14b
	shr rax, cl
	lea rcx, [r10 + r13]
	inc rcx
	or [r11 + rcx*8], rax
.skip:
	dec r10
	jns .r_shift_loop


.add_bit_T: ; T += 4^(n-j)
	; k = 2*(n-j)
	mov r12, rdx
	sub r12, r11
	shl r12, 1

	; l = k % 64
	mov r13, r12
	and r13, 63

	; r = 2^l
	mov r14, 1
	mov cl, r13b
	shl r14, cl

	; for(i=k/64; i<ss; i++)
	mov r10, r12
	shr r10, 6
.add_bit_T_loop:
	mov r13, [rbx + r10*8]
	add [rbx + r10*8], r14
	cmp [rbx + r10*8], r13
	jae .break_add_bit_T_loop
	mov r14, 1
	inc r10
	cmp r9, r10
	jb .add_bit_T_loop
.break_add_bit_T_loop:

.compare:
	; i = ss-1
	mov r10, r9
	dec r10
.compare_loop:
	; X[i] ? T[i]
	mov r12, [rsi + r10*8]
	mov r13, [rbx + r10*8]
	cmp r12, r13
	ja .break_compare_loop ; X[i] > T[i]
	jb .continue_main_loop ; X[i] < T[i]
	dec r10
	jns .compare_loop
.break_compare_loop:

.add_bit_Q:
	; k = n-j
	mov r12, rdx
	sub r12, r11

	; l = k % 64
	mov r13, r12
	and r13, 63

	; r = 2^l
	mov r14, 1
	mov cl, r13b
	shl r14, cl

	; i = n / 64
	mov r10, r12
	shr r10, 6
.add_bit_Q_loop:
	mov r13, [rdi + r10*8]
	add [rdi + r10*8], r14
	cmp [rdi + r10*8], r13
	jae .break_add_bit_Q_loop
	mov r14, 1
	inc r10
	cmp r8, r10
	jb .add_bit_Q_loop
.break_add_bit_Q_loop:

.sub_X_T:
	; r14 - borrow
	xor r14, r14
	; i = 0
	xor r10, r10
.sub_X_T_loop:
	mov r12, [rsi + r10*8]
	sub r12, r14
	mov r13, [rbx + r10*8]
	sub r12, r13
	adc r14, 0
	mov [rsi + r10*8], r12
	inc r10
	cmp r9, r10
	jns .sub_X_T_loop

.continue_main_loop:
	inc r11
	cmp r11, rdx
	jbe .main_loop

	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret