section .bss
    align 4
    length: resd 1

    align 2
    table: resw 176

section .text
global _start

_start:
    mov eax, [rel length]
    lea rax, [rel table]

    mov rax, 0x1
    int 80h