section .text
global _start

; Stałe dla wywołań systemowych i flag
O_RDWR      equ 2
PROT_READ   equ 1
PROT_WRITE  equ 2
MAP_SHARED  equ 1
MS_SYNC     equ 4
S_IFREG     equ 0x8000     ; Stała dla zwykłego pliku

_start:
    ; Sprawdzenie liczby argumentów
    pop rcx                 ; rcx = argc
    cmp rcx, 2              ; oczekujemy dokładnie 2 argumenty
    jne .error              ; jeśli nie, błąd

    ; Pobranie nazwy pliku
    pop rdi                 ; argv[0] (nazwa programu)
    pop rdi                 ; argv[1] (nazwa pliku)

    ; Otwarcie pliku
    mov rax, 2              ; sys_open
    mov rsi, O_RDWR         ; flagi: O_RDWR
    xor rdx, rdx            ; tryb dostępu: 0
    syscall
    test rax, rax           ; sprawdź błąd
    js .error               
    mov r12, rax            ; zapisz deskryptor

    ; Pobranie informacji o pliku
    sub rsp, 144            ; rezerwacja miejsca na struct stat
    mov rax, 5              ; sys_fstat
    mov rdi, r12            ; deskryptor pliku
    mov rsi, rsp            ; wskaźnik na struct stat
    syscall
    test rax, rax           ; sprawdź błąd
    js .fstat_error         

    ; Sprawdź czy to zwykły plik
    mov eax, [rsp + 24]     ; st_mode (offset 24)
    and eax, 0xF000         ; maska dla typu pliku
    cmp eax, S_IFREG        ; czy zwykły plik?
    jne .not_regular        ; błąd jeśli nie

    mov r13, [rsp + 48]     ; st_size (offset 48)
    add rsp, 144            ; przywróć stos

    ; Plik za krótki do odwracania?
    cmp r13, 2
    jl .close_file          

    ; Mapowanie pliku
    mov rax, 9              ; sys_mmap
    xor rdi, rdi            ; addr = NULL
    mov rsi, r13            ; rozmiar pliku
    mov rdx, PROT_READ | PROT_WRITE
    mov r10, MAP_SHARED     ; flags
    mov r8, r12             ; deskryptor
    xor r9, r9              ; offset = 0
    syscall
    test rax, rax           ; sprawdź błąd
    js .close_error         
    mov r14, rax            ; zapisz adres mapy

    ; Odwracanie zawartości
    mov rdi, rax            ; początek danych
    lea rsi, [rax + r13 - 1] ; koniec danych
.reverse_loop:
    cmp rdi, rsi            
    jge .after_reverse      
    mov al, [rdi]           
    mov cl, [rsi]
    mov [rdi], cl
    mov [rsi], al
    inc rdi                 
    dec rsi                 
    jmp .reverse_loop

.after_reverse:
    ; Synchronizuj z dyskiem
    mov rax, 26             ; sys_msync
    mov rdi, r14            ; adres mapy
    mov rsi, r13            ; rozmiar
    mov rdx, MS_SYNC        ; flagi
    syscall
    test rax, rax           
    js .unmap_close_error   

    ; Odmapuj plik
    mov rax, 11             ; sys_munmap
    mov rdi, r14            
    mov rsi, r13            
    syscall
    test rax, rax           
    js .close_error         

.close_file:
    ; Zamknij plik
    mov rax, 3              ; sys_close
    mov rdi, r12            
    syscall
    test rax, rax           
    js .error               

    ; Zakończ sukcesem
    xor rdi, rdi            
    jmp .exit

.unmap_close_error:
    ; Sprzątanie po błędzie msync
    mov rax, 11             ; sys_munmap
    mov rdi, r14
    mov rsi, r13
    syscall

.fstat_error:
    ; Przywróć stos po błędzie fstat
    add rsp, 144
    jmp .close_error

.not_regular:
    ; Obsłuż nie-zwykły plik
    add rsp, 144
    jmp .close_error

.close_error:
    ; Zamknij plik po błędzie
    mov rax, 3              ; sys_close
    mov rdi, r12
    syscall

.error:
    ; Zakończ z błędem
    mov rdi, 1

.exit:
    ; Wyjdź
    mov rax, 60             ; sys_exit
    syscall