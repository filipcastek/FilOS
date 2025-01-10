#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include <stddef.h>

// Definice maximálního počtu procesů v systému
#define MAX_PROCESSES 64

// Definice stavů procesu
typedef enum {
    PROCESS_RUNNING,     // Proces běží
    PROCESS_READY,       // Proces je připraven k běhu
    PROCESS_BLOCKED,     // Proces je zablokován (např. čeká na I/O)
    PROCESS_TERMINATED   // Proces byl ukončen
} process_state_t;

// Struktura pro uložení informací o procesu
typedef struct {
    uint32_t pid;               // Unikátní ID procesu
    uint32_t ppid;              // ID rodičovského procesu
    process_state_t state;      // Stav procesu
    uint32_t *stack;            // Ukazatel na zásobník procesu
    uint32_t *stack_pointer;    // Ukazatel na aktuální pozici zásobníku
    uint32_t entry_point;       // Adresa, na kterou proces začne běžet
    uint32_t priority;          // Priorita procesu
    uint32_t cpu_time;          // Celkový čas běhu na CPU
} process_t;

// Deklarace procesorového plánu
extern process_t processes[MAX_PROCESSES];
extern uint32_t current_process_index;

// Funkce pro vytvoření nového procesu
int create_process(uint32_t entry_point, uint32_t priority);

// Funkce pro ukončení procesu
void terminate_process(uint32_t pid);

// Funkce pro plánování procesu (scheduling)
void schedule_processes();

// Funkce pro přepnutí kontextu mezi procesy (context switch)
void context_switch(uint32_t next_process);

// Funkce pro nastavení stavu procesu
void set_process_state(uint32_t pid, process_state_t state);

// Funkce pro získání aktuálního procesu
process_t *get_current_process();

#endif // PROCESS_H
