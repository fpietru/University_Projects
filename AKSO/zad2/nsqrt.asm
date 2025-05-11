section .bss
    align 8
    T: resq 8000

section .text
global nsqrt

; Argumenty:
; rdi - wskaznik do tablicy Q
; rsi - wskaznik do tablicy X
; rdx - wartosc n 

nsqrt:
    ; r8 - s := dlugosc tablicy Q
    mov r8, rdx
    shr r8, 0x6 ; s = n >> 6
    ; r9 - ss := dlugosc tablicy X, T
    lea r9, [r8 + r8] ; ss = 2 * s
    mov r11, [rel T] ; r11 := adres tablicy T

    ; czyszczenie Q
    mov r10, 0x0 ; r10 - j = 0
.clean_Q_loop:
    mov qword [rdi + r10 * 8], 0x0
    inc r10
    cmp r10, r8
    jns .clean_Q_loop

    ; iteracyjnie wyliczanie Q
    mov rcx, 0x1 ; rcx - i = 1
.main_loop:

    ; czyszczenie T
    mov r10, 0x0 ; r10 - j = 0
.clean_T_loop:
    mov qword [r11 + r10 * 8], 0x0
    inc r10
    cmp r10, r9
    jb .clean_T_loop


    ret


