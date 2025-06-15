; Autor: Franciszek Pietrusiak
global _start
section .text

; Stale dla wywolan systemowych i flag
O_RDWR      equ 2       ; sys_open: odczyt i zapis
PROT_READ   equ 1       ; sys_mmap: odczyt pliku 
PROT_WRITE  equ 2       ; sys_mmap: zapis do pliku
MAP_SHARED  equ 1       ; sys_mmap: dzielone mapowanie pliku
MS_SYNC     equ 4       ; sys_msync: wymusza natychmiastowy zapis
STAT_SIZE   equ 144     ; sys_fstat: rozmiar struct stat
ST_MODE     equ 24      ; sys_fstat: typ pliku i prawa
ST_SIZE     equ 48      ; sys_fstat: rozmiar pliku
S_IFREG     equ 0x8000  ; kod zwyklego pliku

; Numery funkcji systemowych
SYS_OPEN    equ 2
SYS_CLOSE   equ 3
SYS_FSTAT   equ 5
SYS_MMAP    equ 9
SYS_MUNMAP  equ 11
SYS_MSYNC   equ 26
SYS_EXIT    equ 60

_start:
    ; Sprawdza liczbe argumentow
    pop rcx                 ; rcx = argc
    cmp rcx, 2              ; program ma dostac dokladnie 2 argumenty
    jne .error              ; jesli tak nie jest => blad

    ; Pobiera nazwy
    pop rdi                 ; argv[0] = nazwa programu
    pop rdi                 ; argv[1] = nazwa pliku

    ; Otwiera plik
    mov rax, SYS_OPEN       ; sys_open
    mov rsi, O_RDWR         ; flaga: O_RDWR
    xor rdx, rdx            ; tryb dostepu = 0
    syscall
    test rax, rax           ; sprawdza blad
    js .error
    mov r12, rax            ; zapisuje deskryptor

    ; Pobiera informacje o pliku
    sub rsp, STAT_SIZE      ; rezerwuje bufor na struct stat
    mov rax, SYS_FSTAT      ; sys_fstat
    mov rdi, r12            ; deskryptor pliku
    mov rsi, rsp            ; wskaznik na struct stat
    syscall
    test rax, rax
    js .revert_stack

    ; Sprawdza czy plik jest zwykly
    mov eax, [rsp+ST_MODE]
    and eax, 0xF000         ; sprawdza tylko typ
    cmp eax, S_IFREG        ; porownuje z kodem zwyklego pliku
    jne .revert_stack

    mov r13, [rsp+ST_SIZE]
    add rsp, STAT_SIZE      ; zwalnia bufor na struct stat

    ; Sprawdza czy plik nie jest za krotki
    ; jesli plik ma mniej niz 2 bajty to nie trzeba go odwracac
    cmp r13, 2
    jl .close_file

    ; Mapuje plik do pamieci
    mov rax, SYS_MMAP
    xor rdi, rdi            ; addr = NULL
    mov rsi, r13            ; length = rozmiar pliku w r13
    mov rdx, PROT_READ | PROT_WRITE
    mov r10, MAP_SHARED
    mov r8, r12             ; deskryptor
    xor r9, r9              ; offset = 0
    syscall
    test rax, rax
    js .close_error
    mov r14, rax            ; r14 = adres mapowanej pamieci

    ; Odwraca plik
    mov rdi, rax            ; rdi = poczatek
    lea rsi, [rax+r13-1]    ; rsi = koniec
.reverse_loop:
    cmp rdi, rsi
    jge .after_reverse      ; jesli wskazniki sie minely => koniec
    mov al, [rdi]           ; al = bajt z poczatku
    mov cl, [rsi]           ; cl = bajt z konca
    mov [rdi], cl           ; swap
    mov [rsi], al
    inc rdi
    dec rsi
    jmp .reverse_loop

    ; Zapisuje zmiany na dysku
.after_reverse:
    mov rax, SYS_MSYNC
    mov rdi, r14            ; adres mapowanej pamieci
    mov rsi, r13            ; rozmiar
    mov rdx, MS_SYNC        ; flaga: MS_SYNC
    syscall
    test rax, rax
    js .unmap_close_error

    ; Zwalnia zmapowana pamiec
    mov rax, SYS_MUNMAP
    mov rdi, r14            ; adres mapowanej pamieci
    mov rsi, r13            ; rozmiar
    syscall
    test rax, rax
    js .close_error

    ; Zamyka plik
.close_file:
    mov rax, SYS_CLOSE
    mov rdi, r12            ; deskryptor
    syscall
    test rax, rax
    js .error

    ; Konczy program z sukcesem
    xor rdi, rdi            ; kod wyjscia = 0
    jmp .exit

    ; Sprzata po bledzie sys_msync
.unmap_close_error:
    ; Zwalnia zmapowana pamiec
    mov rax, SYS_MUNMAP
    mov rdi, r14            ; adres mapowanej pamieci
    mov rsi, r13            ; rozmiar
    syscall
    jmp .close_error

    ; Przywraca stos
.revert_stack:
    add rsp, STAT_SIZE
    jmp .close_error

    ; Zamyka plik po bledzie
.close_error:
    mov rax, SYS_CLOSE
    mov rdi, r12
    syscall

    ; Ustawia kod wyjscia na 1
.error:
    mov rdi, 1

    ; Konczy program
.exit:
    mov rax, SYS_EXIT
    syscall
