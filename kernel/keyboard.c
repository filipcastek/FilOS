#include "keyboard.h"
#include "screen.h"
#include "interrupts.h"

static char keyboard_buffer[BUFFER_SIZE];
static int buffer_head = 0;
static int buffer_tail = 0;

// skenovaci kody -> ascii
static char scancode_to_ascii[256] = {
    0, 0, 0, 0, 0, 0, 0, 0,    // 0x00-0x07
    0, 0, 0, 0, 0, 0, 0, 0,    // 0x08-0x0F
    '1', '2', '3', '4', '5', '6', '7', '8', // 0x10-0x17
    '9', '0', '-', '=', 0, 0, 0, 0,    // 0x18-0x1F
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', // 0x20-0x27
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', // 0x28-0x2F
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', // 0x30-0x37
    'Y', 'Z', '[', '\\', ']', 0, 0, 0,    // 0x38-0x3F
    0, 0, 0, 0, 0, 0, 0, 0,    // 0x40-0x47
    0, 0, 0, 0, 0, 0, 0, 0,    // 0x48-0x4F
    0, 0, 0, 0, 0, 0, 0, 0,    // 0x50-0x57
    0, 0, 0, 0, 0, 0, 0, 0,    // 0x58-0x5F
    ' ', 0, 0, 0, 0, 0, 0, 0,    // 0x60-0x67
    0, 0, 0, 0, 0, 0, 0, 0,    // 0x68-0x6F
    0, 0, 0, 0, 0, 0, 0, 0,    // 0x70-0x77
    0, 0, 0, 0, 0, 0, 0, 0,    // 0x78-0x7F
};

// init a preruseni
void init_keyboard() {
    print_string("Inicializace klávesnice...\n");

    // init hw, inter
    init_interrupts();
}

// sc->ascii
char scan_code_to_ascii(uint8_t scan_code) {
    if (scan_code < 256) {
        return scancode_to_ascii[scan_code];
    }
    return 0; // Pokud není platný skenovací kód
}

// inter-obsluha
void keyboard_handler() {
    uint8_t scan_code = inb(0x60);  //ox60 port-sken

    // if bfr == plny: vyser se na to
    if ((buffer_head + 1) % BUFFER_SIZE == buffer_tail) {
        return;
    }

    //scan - ascii znak
    char ascii = scan_code_to_ascii(scan_code);
    if (ascii != 0) {
        // pridani ascii do bufferu
        keyboard_buffer[buffer_head] = ascii;
        buffer_head = (buffer_head + 1) % BUFFER_SIZE;
    }
}

// cteni znaku z bf
char read_key() {
    if (buffer_head == buffer_tail) {
        return 0;  // buf 0 - 0
    }

    char key = keyboard_buffer[buffer_tail];
    buffer_tail = (buffer_tail + 1) % BUFFER_SIZE;
    return key;
}
