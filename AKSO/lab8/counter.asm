section .data
    count:  dq 0       ; 64-bitowy licznik wywołań

section .text
    global counter

counter:
    ; Zwiększ wartość pod count o 1
    inc qword [count]

    ; Załaduj aktualną wartość (po inkrementacji) do rejestru RAX
    mov rax, [count]

    ; Zwróć wynik jako unsigned int (tylko dolne 32 bity RAX są używane)
    ret