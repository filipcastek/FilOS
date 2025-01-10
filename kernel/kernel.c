#include "screen.h"
#include "memory.h"
#include "interrupts.h"
#include "process.h"
#include "syscall.h"
#include "timer.h"
#include "keyboard.h"
#define first_process my_first_process

void my_first_process() {
    print_string("INICIALIZACE_USPESNA");
    while(1) {
      
    }
}
void kernel_main() {
    init_screen();          // Inicializace obrazovky
    init_memory(1024);      // Inicializace paměti s velikostí 1024
    init_interrupts();      // Inicializace přerušení
    init_timer();           // Inicializace časovače
    init_keyboard();        // Inicializace klávesnice

    // prvni proces
    create_process(&first_process, 0, 0);

    print_string("FilOS.SPUSTENY.\n");

    // main loop os
    while (1) {
        //multitasking
        schedule();
    }
}
