#include "screen.h"

static char* video_memory = (char*) 0xB8000;  // Začátek videopaměti pro textový režim

void print_char(char c) {
    *video_memory = c;
    video_memory++;
    *video_memory = 0x07;  // Barva textu (bílá)
    video_memory++;
}

void print_string(const char* str) {
    while (*str) {
        print_char(*str++);
    }
}

void init_screen() {
    print_string("Obrazovka inicializovana.\n");
}
