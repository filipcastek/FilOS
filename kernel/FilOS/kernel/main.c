#include "kernel.h"
#include "screen.h"
#include "interrupts.h"

void kernel_main() {
    clear_screen();
    print_string("vitejte.v.FilOS\n");
    print_string("Priprava.systemu\n");

    init_gdt();  // Inicializace GDT
    init_interrupts();  // Inicializace přerušení

    print_string("System.je.pripraven!\n");

    // Vytvoř zde hlavní smyčku jádra
    while (1) {
        
    }
}
