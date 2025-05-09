global mac0

; Argumenty funkcji mac0:
; rdi - wartosc a
; rsi - wartosc x
; rdx - wartosc y

mac0:
  imul rsi, rdx
  lea rax, [rdi+rsi]
  ret

