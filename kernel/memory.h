#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>  // Pro velikost typu size_t

// Velikost stránky (v bytech), typicky 4 KB
#define PAGE_SIZE 4096

// Struktura pro paměťový blok
typedef struct MemoryBlock {
    void *address;    // Adresa paměti
    size_t size;      // Velikost alokovaného bloku
    struct MemoryBlock *next;  // Ukazatel na další blok
} MemoryBlock;

// Funkce pro inicializaci paměti
void init_memory(void *start, size_t size);

// Funkce pro alokaci paměti
void *malloc(size_t size);

// Funkce pro de-alokaci paměti
void free(void *ptr);

// Funkce pro inicializaci paměťového spravování (alokace a de-alokace)
void *memcpy(void *dest, const void *src, size_t n);

// Funkce pro nastavení bloků paměti na určitou hodnotu
void *memset(void *ptr, int value, size_t num);

// Funkce pro kontrolu správnosti alokace
void check_allocation(void *ptr);

// Funkce pro zobrazení dostupné paměti (pro ladění)
void debug_memory_info();

#endif // MEMORY_H
