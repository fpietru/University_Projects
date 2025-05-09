global mac2

; Argumenty do funkcji mac2
; rdi - wskaznik do a
; rsi - wskaznik do x
; rdx - wskaznik do y

mac2:
  ; mnozenie na krzyz x_lo razy y_hi
  ; oraz y_lo razy x_hi
  mov r8, [rsi]      ; r8 - wartosc x_lo
  mov r9, [rdx]      ; r9 - wartosc y_lo
  imul r8, [rdx + 8] ; x_lo * y_hi
  imul r9, [rsi + 8] ; y_lo * x_hi

  mov rax, [rsi]
  mul qword [rdx] 

  ; dodaje starsze czesci x, y
  add rdx, r8
  add rdx, r9

  ; dodaje iloczyn do a
  add [rdi], rax
  adc [rdi + 8], rdx

  ; wynik jest w [rdi], [rdi + 8]
  ret