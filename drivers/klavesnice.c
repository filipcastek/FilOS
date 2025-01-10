#include <stdint.h>
#include <stdbool.h>
#include "io.h"

#define PORT_KBD_DATA 0x60
#define PORT_KBD_STATUS 0x64
#define PORT_KBD_CMD 0x64

#define KBD_STATUS_MASK_OUT_BUF 1

static bool klavesnice_pripravena() {
    return inb(PORT_KBD_STATUS) & KBD_STATUS_MASK_OUT_BUF;
}

static uint8_t klavesnice_cti_scancode() {
    while (!klavesnice_pripravena());
    return inb(PORT_KBD_DATA);
}

void klavesnice_inicializace() {
    // Inicializace klávesnice, pokud je potřeba
}

void klavesnice_obsluha() {
    uint8_t scancode = klavesnice_cti_scancode();
    // Zpracování scancode, například převod na ASCII a odeslání do bufferu
}

void klavesnice_irq() {
    // Obsluha přerušení klávesnice
    klavesnice_obsluha();
}