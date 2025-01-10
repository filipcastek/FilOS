#include <stdint.h>
#include <stddef.h>

#define VGA_SIRKA 80
#define VGA_VYSKA 25
#define VGA_PAMET (uint16_t*)0xB8000

enum vga_barva {
    VGA_BARVA_CERNA = 0,
    VGA_BARVA_MODRA = 1,
    VGA_BARVA_ZELENA = 2,
    VGA_BARVA_AZUROVA = 3,
    VGA_BARVA_CERVENA = 4,
    VGA_BARVA_MAGENTA = 5,
    VGA_BARVA_HNEDA = 6,
    VGA_BARVA_SVETLE_SEDA = 7,
    VGA_BARVA_TMAVE_SEDA = 8,
    VGA_BARVA_SVETLE_MODRA = 9,
    VGA_BARVA_SVETLE_ZELENA = 10,
    VGA_BARVA_SVETLE_AZUROVA = 11,
    VGA_BARVA_SVETLE_CERVENA = 12,
    VGA_BARVA_SVETLE_MAGENTA = 13,
    VGA_BARVA_SVETLE_HNEDA = 14,
    VGA_BARVA_BILA = 15,
};

static inline uint8_t vga_zaznam_barva(enum vga_barva fg, enum vga_barva bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_zaznam(unsigned char uc, uint8_t barva) {
    return (uint16_t) uc | (uint16_t) barva << 8;
}

static size_t terminal_radek;
static size_t terminal_sloupec;
static uint8_t terminal_barva;
static uint16_t* terminal_buffer;

void terminal_inicializace(void) {
    terminal_radek = 0;
    terminal_sloupec = 0;
    terminal_barva = vga_zaznam_barva(VGA_BARVA_SVETLE_SEDA, VGA_BARVA_CERNA);
    terminal_buffer = VGA_PAMET;
    for (size_t y = 0; y < VGA_VYSKA; y++) {
        for (size_t x = 0; x < VGA_SIRKA; x++) {
            const size_t index = y * VGA_SIRKA + x;
            terminal_buffer[index] = vga_zaznam(' ', terminal_barva);
        }
    }
}

void terminal_nastavit_barvu(uint8_t barva) {
    terminal_barva = barva;
}

void terminal_zapsat_na_pozici(char c, uint8_t barva, size_t x, size_t y) {
    const size_t index = y * VGA_SIRKA + x;
    terminal_buffer[index] = vga_zaznam(c, barva);
}

void terminal_zapsat_znak(char c) {
    if (c == '\n') {
        terminal_sloupec = 0;
        if (++terminal_radek == VGA_VYSKA) {
            terminal_radek = 0;
        }
    } else {
        terminal_zapsat_na_pozici(c, terminal_barva, terminal_sloupec, terminal_radek);
        if (++terminal_sloupec == VGA_SIRKA) {
            terminal_sloupec = 0;
            if (++terminal_radek == VGA_VYSKA) {
                terminal_radek = 0;
            }
        }
    }
}

void terminal_zapsat(const char* data, size_t velikost) {
    for (size_t i = 0; i < velikost; i++) {
        terminal_zapsat_znak(data[i]);
    }
}

void terminal_zapsat_retezec(const char* data) {
    terminal_zapsat(data, strlen(data));
}