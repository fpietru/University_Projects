global counter

section .bss
    count:  resq 1

section .text

counter:
    inc qword [rel count]
    mov rax, [rel count]
    ret
