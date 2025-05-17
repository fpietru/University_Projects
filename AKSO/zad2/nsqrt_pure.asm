; Autor: Franciszek Pietrusiak
; Implementuje sugerowany algorytm
section .bss
	align 8
	T: resq 8000                 ; z zal 64 <= n <= 256000

section .text
global nsqrt

; Rejestry:
; rdi - wskaznik do tablicy Q
; rsi - wskaznik do tablicy X
; rdx - wartosc n
; rbx - adres tablicy T
; r8 - s := dlugosc tablicy Q
; r9 - ss := dlugosc tablicy X, T
; r10 - i := iterator
; r11 - j := iterator
; r12 - k := zmienna lokalna
; r13 - l := zmienna lokalna
; r14 - r := zmienna lokalna
; r15 - x := zmienna lokalna
; rax - y := zmienna lokalna
; rcx - z := zmienna lokalna

%macro clean 2                       ; for (i=0; i<%2; i++) { (%1)[i] = 0 }
	push rdi
	mov rdi, %1
	mov rcx, %2
	xor rax, rax
	rep stosq 
	pop rdi
%endmacro

nsqrt:
	push rbx
	push r12
	push r13
	push r14
	push r15

	mov r8, rdx                  ; r8 - s := dlugosc tablicy Q
	shr r8, 6                    ; s = n / 64 = n >> 6
	lea r9, [r8 + r8]            ; r9 - ss = 2 * s := dlugosc tablicy X, T
	lea rbx, [rel T]             ; rbx := adres tablicy T

	clean rdi, r8                ; czyszczenie Q

	                             ; iteracyjnie wyliczanie Q
	mov r11, 1                   ; r11 - j = 1
.main_loop:                          ; for (j=1; j<=n; j++)
		
	                             ; r12 - k := n-j+1
	mov r12, rdx                 ; k = n
	sub r12, r11                 ; k -= j
	inc r12                      ; k++

	                             ; r13 - l := k / 64 = k >> 6
	mov r13, r12                 ; l = k
	shr r13, 6                   ; l >>= 6

	clean rbx, r9                ; czyszczenie T

.r_shift:                            ; T += 2^(n-j+1)*Q

	                             ; r14 - r := k % 6 = k & 63
	mov r14, r12                 ; r = k
	and r14, 63                  ; r &= 63

	mov r10, r8
	dec r10
.r_shift_loop:                       ; for (i=s-1; i>=0; i--)
	mov r15, qword [rdi + r10*8] ; x = Q[i]

	                             ; T[i+l] = y = x << r
	mov rax, r15                 ; y = x
	mov cl, r14b                 ; z = r
	shl rax, cl                  ; x <<= z
	lea rcx, [r10 + r13]         ; z = i + l
	mov qword [rbx + rcx*8], rax ; T[z] = x

	                             ; if (r != 0 && i+l+1 < ss)
	test r14, r14
	jz .skip                     ; if (r == 0)

	                             ; y = i+l+1
	mov rax, r10                 ; y = i
	add rax, r13                 ; y += l
	inc rax                      ; y++
	cmp rax, r9
	jae .skip                    ; if (y >= ss)

	                             ; T[i+l+1] |= Q[i] >> (64 - r)
	mov rax, r15                 ; y = x = Q[i]
	mov cl, 64                   ; z = 64
	sub cl, r14b                 ; z -= r
	shr rax, cl                  ; y >>= z
	lea rcx, [r10 + r13]         ; z = i + l
	inc rcx                      ; z++
	or [rbx + rcx*8], rax        ; T[z] |= y
.skip:
	dec r10
	jns .r_shift_loop


.add_bit_T: ; T += 4^(n-j)
	; k = 2*(n-j)
	mov r12, rdx                 ; k = n
	sub r12, r11                 ; k -= j
	shl r12, 1                   ; k <<= 2

	; l = k % 64
	mov r13, r12                 ; l = k
	and r13, 63                  ; l &= 63

	; r = 2^l
	mov r14, 1                   ; r = 1
	mov cl, r13b
	shl r14, cl                  ; r <<= l

	mov r10, r12                 ; i = k
	shr r10, 6                   ; i >>= 6
.add_bit_T_loop:                     ; for (i=k/64; i<ss; i++)
	mov r13, [rbx + r10*8]       ; l = T[i]
	add [rbx + r10*8], r14       ; T[i] += r
	cmp [rbx + r10*8], r13
	jae .break_add_bit_T_loop    ; if (T[i] >= r)
	mov r14, 1                   ; r = 1
	inc r10
	cmp r9, r10
	jb .add_bit_T_loop
.break_add_bit_T_loop:

.compare:
	mov r10, r9                  ; i = ss
	dec r10                      ; i--
.compare_loop:
	                             ; X[i] ? T[i]
	mov r12, [rsi + r10*8]       ; k = X[i]
	mov r13, [rbx + r10*8]       ; l = T[i]
	cmp r12, r13
	ja .break_compare_loop       ; if (k > l)
	jb .continue_main_loop       ; if (k < l)
	dec r10
	jns .compare_loop
.break_compare_loop:

.add_bit_Q:
	                             ; k = n-j
	mov r12, rdx                 ; k = n
	sub r12, r11                 ; k -= r11

	                             ; l = k % 64
	mov r13, r12                 ; l = k
	and r13, 63                  ; l &= 63

	                             ; r = 2^l
	mov r14, 1
	mov cl, r13b
	shl r14, cl

	mov r10, r12
	shr r10, 6
.add_bit_Q_loop:                     ; for (i=i/64; i<s; i++)
	mov r13, [rdi + r10*8]       ; l = Q[i]
	add [rdi + r10*8], r14       ; Q[i] += r
	cmp [rdi + r10*8], r13
	jae .break_add_bit_Q_loop    ; if (Q[i] >= l)
	mov r14, 1                   ; r = 1
	inc r10
	cmp r10, r8
	jb .add_bit_Q_loop
.break_add_bit_Q_loop:

.sub_X_T:
	xor r14, r14                 ; r = 0
	xor r10, r10                 ; i = 0
.sub_X_T_loop:
	mov r12, [rsi + r10*8]       ; k = X[i]
	sub r12, r14                 ; k -= r
	mov r13, [rbx + r10*8]       ; l = T[i]
	cmp r12, r13
	setb r14b
	sub r12, r13                 ; k -= l
	mov [rsi + r10*8], r12       ; X[i] = k
	inc r10
	cmp r10, r9
	jb .sub_X_T_loop

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
