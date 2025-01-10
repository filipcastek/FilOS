#include "memory.h"
#include <stddef.h>
#include <stdint.h>

// Ukazatel na začátek paměti (pro jednoduchost používáme statický ukazatel)
static uint8_t *memory_start;
static MemoryBlock *free_list = NULL;  // Seznam volných bloků paměti

// Inicializace paměti
void init_memory(void *start, size_t size) {
    memory_start = (uint8_t *)start;
    free_list = (MemoryBlock *)memory_start;

    // Inicializace prvního bloku jako celé paměti
    free_list->address = memory_start;
    free_list->size = size;
    free_list->next = NULL;
}

// Alokace paměti
void *malloc(size_t size) {
    MemoryBlock *prev = NULL;
    MemoryBlock *current = free_list;

    // Procházení seznamu volných bloků
    while (current != NULL) {
        if (current->size >= size) {
            // Pokud najdeme dostatečně velký blok
            if (current->size > size + sizeof(MemoryBlock)) {
                // Pokud je zbývající místo dostatečně velké pro nový blok
                MemoryBlock *new_block = (MemoryBlock *)((uint8_t *)current + size);
                new_block->address = (uint8_t *)current + size;
                new_block->size = current->size - size;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }

            if (prev != NULL) {
                prev->next = current->next;
            } else {
                free_list = current->next;
            }

            return current->address;
        }
        prev = current;
        current = current->next;
    }

    // Pokud není dostatečná paměť
    return NULL;
}

// De-alokace paměti
void free(void *ptr) {
    MemoryBlock *block = (MemoryBlock *)((uint8_t *)ptr - sizeof(MemoryBlock));
    
    // Přidání bloku zpět do seznamu volných bloků
    block->next = free_list;
    free_list = block;
}

// Ladění - zobrazení informací o alokovaných blocích
void debug_memory_info() {
    MemoryBlock *current = free_list;
    while (current != NULL) {
        // Vytisknout informace o každém bloku
        // Předpokládáme, že máme funkci pro tisk (např. printf)
        // printf("Blok: %p, velikost: %zu\n", current->address, current->size);
        current = current->next;
    }
}
