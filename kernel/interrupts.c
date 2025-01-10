#include "interrupts.h"
#include "screen.h"

void init_interrupts() {
    print_string("Inicializace preruseni...\n");

    // Příklad inicializace IDT (tabulka přerušení)
}

void interrupt_handler() {
    print_string("Bylo zpracováno preruseni!\n");
}
