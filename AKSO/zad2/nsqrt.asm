; Autor: Franciszek Pietrusiak
; Implementuje Sugerowany Algorytm

section .bss
	align 8
	T: resq 8000                 ; T - tablica pomocnicza
                                     ; z zalozenia 64 <= n <= 256000
                                     ; wiec rozmiar w przedziale [1, 8000]

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
; r12 - k := zmienna pomocnicza
; r13 - l := zmienna pomocnicza
; r14 - r := zmienna pomocnicza
; r15 := zmienna pomocnicza
; rcx := zmienna pomocnicza

%define ADD_BIT_Q_NO  0
%define ADD_BIT_Q_YES 1

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

	mov r12, rdi                 ; czyszczenie Q[0 .. s]
	mov rcx, r8
	xor rax, rax
	rep stosq
	mov rdi, r12

	                             ; iteracyjnie wyliczanie Q
	mov r11, 1
.main_loop:                          ; for (j=1; j<=n; j++)
	mov r15, ADD_BIT_Q_NO        ; r15 - flaga czy wykonac Q += 2^(n-j)

.r_shift:                            ; T += 2^(n-j+1)*Q
	
	                             ; k = n-j+1
	mov r12, rdx
	sub r12, r11
	inc r12
	                             ; l = k / 64 = k >> 6
	mov r13, r12
	shr r13, 6
	                             ; Czyszczenie T[0 .. r13-1]	
	mov r10, rdi
	mov rdi, rbx
	mov rcx, r13
	xor rax, rax
	rep stosq
	                             ; Czyszczenie T[r13+r8 .. r9-1]
	lea rdi, [rbx + r13*8]
	mov rax, r8
	shl rax, 3
	add rdi, rax
	mov rcx, r9
	sub rcx, r13
	sub rcx, r8
	xor rax, rax
	rep stosq
	mov rdi, r10
	                             ; r := k % 64 = k & 63
	mov r14, r12
	and r14, 63
                                     ; i = s - 1
	mov r10, r8
	dec r10
.r_shift_loop:                       ; T[i+l] = Q[i] << r
	mov r12, qword [rdi + r10*8]
	mov cl, r14b
	shl r12, cl
	lea rcx, [r10 + r13]
	mov qword [rbx + rcx*8], r12

	                             ; if (r != 0 && i+l+1 < ss) 
	test r14, r14
	jz .skip                     ; jesli: r == 0
	mov r12, r10
	add r12, r13
	inc r12
	cmp r12, r9
	jae .skip                    ; jesli: i+l+1 >= ss

	                             ; T[i+l+1] |= Q[i] >> (64 - r)
	mov r12, qword [rdi + r10*8]
	mov cl, 64
	sub cl, r14b
	shr r12, cl
	lea rcx, [r10 + r13]
	inc rcx
	or [rbx + rcx*8], r12
.skip:
	dec r10
	jns .r_shift_loop

	                             ; k = 2*(n-j)
	mov r12, rdx
	sub r12, r11                 
	shl r12, 1                   

	mov rcx, rbx
.add_bit:                            ; dodaj 2^k do liczby reprezentowanej
                                     ; przez tablice na ktora wskazuje rcx

	                             ; l = k % 64
	mov r13, r12
	and r13, 63
	                             ; r = 2^l
	xor r14, r14
	bts r14, r13
                                     ; i = k / 64
	mov r10, r12
	shr r10, 6
.add_bit_loop:                       ; for (i=k/64; i<ss; i++)
	mov r13, [rcx + r10*8]
	add [rcx + r10*8], r14
	cmp [rcx + r10*8], r13
	jae .break_add_bit_loop      ; if (T[i] >= r)
	mov r14, 1
	inc r10
	cmp r9, r10
	jb .add_bit_loop
.break_add_bit_loop:


	cmp r15, ADD_BIT_Q_YES
	je .sub_X_T

.compare:                            ; porownaj X i T ze soba
	mov r10, r9                  ; jesli X >= T to wykonaj .sub_X_T
	dec r10                      ; wpp przejdz do nastepnego j

.compare_loop:	                     ; X[i] ? T[i]
	mov r12, [rsi + r10*8]
	mov r13, [rbx + r10*8]
	cmp r12, r13
	ja .break_compare_loop       ; if (X[i] > T[i])
	jb .continue_main_loop       ; if (X[i] < T[i])
	dec r10
	jns .compare_loop

.break_compare_loop:                 ; Q += 2^(n-j)
	mov r12, rdx
	sub r12, r11
	mov rcx, rdi
	mov r15, ADD_BIT_Q_YES
	jmp .add_bit

.sub_X_T:                            ; X -= T 
	xor r14, r14                 ; r14 - porzyczenie przy odejmowaniu
	xor r10, r10
.sub_X_T_loop:
	mov r12, [rsi + r10*8]
	sub r12, r14            
	mov r13, [rbx + r10*8]
	sub r12, r13
	setc r14b
	mov [rsi + r10*8], r12
	inc r10
	cmp r10, r9
	jb .sub_X_T_loop

.continue_main_loop:
	inc r11
	cmp r11, rdx
	jbe .main_loop
                                     ; zwroc caller-saved rejestry
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret
