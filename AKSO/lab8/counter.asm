section .bss
    count:  resq 1       ; 64-bitowy licznik wywołań

section .text
    global counter

counter:
    ; Zwiększ wartość pod count o 1
    inc qword [rel count]

    ; Załaduj aktualną wartość (po inkrementacji) do rejestru RAX
    mov rax, [rel count]

    ; Zwróć wynik jako unsigned int (tylko dolne 32 bity RAX są używane)
    ret
