global called

section .text

called:
  mov eax, esp  ; Starsze bity wskaźnika stosu nie są nam potrzebne.
  and al, 0xF
  cmp al, 0x8   ; Wskaźnik stosu musi być odpowiednio wyrównany.
  jne .fail
  lea eax, [rdi + 1]
  ret
.fail:
  mov eax, -1
  ret
