[bits 16]
[org 0x7c00]

start:
    cli                      ; Zakáže přerušení
    xor ax, ax               ; Vynuluje registr AX
    mov ax, 0x07C0           ; Nastaví segment pro bootloader
    mov ds, ax
    mov es, ax               ; Nastaví ES na stejný segment jako DS

    ; Načte jádro do paměti
    mov si, kernel_load_addr ; Adresa, kam se má jádro načíst
    mov di, 0x1000           ; Začátek adresy pro kernel
    mov cx, 128              ; Počet bloků pro načtení
load_kernel:
    lodsb
    stosb                    ; Uloží obsah AL do ES:[DI] a inkrementuje DI
    loop load_kernel

    ; Přechod na jádro
    jmp 0x1000:0x0000        ; Skok na adresu jádra

kernel_load_addr:
    db 'FilOS', 0            ; Informace o operačním systému
    times 510 - ($ - $$) db 0 ; Vyplní zbývající místo na 512 bytech
    dw 0xAA55                ; Magic číslo pro boot sektor
