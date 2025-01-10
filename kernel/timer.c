#include "timer.h"
#include "screen.h"

void init_timer() {
    print_string("Inicializace casovace...\n");
}

void timer_handler() {
    print_string("Casovy interrupt!\n");
}
