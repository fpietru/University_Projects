global mac1

; rdi - wartosc a.lo
; rsi - wartosc a.hi
; rdx - wartosc x
; rcx - wartosc y
mac1:
  mov rax, rdx
  mul rcx
  add rax, rdi
  adc rdx, rsi
  ret
