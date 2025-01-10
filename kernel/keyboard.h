#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

// Definice skenovacích kódů pro některé klávesy (můžete přidat další podle potřeby)
#define KEY_A 0x1E
#define KEY_B 0x30
#define KEY_C 0x2E
#define KEY_ENTER 0x1C
#define KEY_BACKSPACE 0x0E
#define KEY_SHIFT 0x2A
#define KEY_CTRL 0x1D
#define KEY_ALT 0x38
#define KEY_SPACE 0x39

// Klávesnice vstupní buffer - velikost bufferu
#define BUFFER_SIZE 128

// Funkce pro inicializaci klávesnice
void init_keyboard();

// Funkce pro čtení znaků z bufferu
char read_key();

// Funkce pro obsluhu klávesnice při přerušení
void keyboard_handler();

// Funkce pro převod skenovacích kódů na ASCII
char scan_code_to_ascii(uint8_t scan_code);

// Funkce pro kontrolu stisku modifikační klávesy (shift, ctrl, alt)
int is_shift_pressed();
int is_ctrl_pressed();
int is_alt_pressed();

#endif // KEYBOARD_H
