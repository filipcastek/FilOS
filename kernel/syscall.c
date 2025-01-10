#include "syscall.h"
#include "screen.h"

void syscall_print(const char* str) {
    print_string(str);
}

void syscall_exit() {
    print_string("Proces ukončen.\n");
    // Ukončení procesu (v jednoduché verzi)
}
