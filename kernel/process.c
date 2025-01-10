#include "process.h"
#include "memory.h"
#include "syscall.h"

#define MAX_PROCESSES 32

typedef struct process {
    uint32_t pid;
    uint32_t esp;
    uint32_t ebp;
    uint32_t eip;
    bool active;
} process_t;

static process_t processes[MAX_PROCESSES];
static uint32_t next_pid = 1;

void init_processes() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i].pid = 0;
        processes[i].active = false;
    }
}

process_t* create_process(void (*entry_point)()) {
    process_t* proc = NULL;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (!processes[i].active) {
            proc = &processes[i];
            proc->pid = next_pid++;
            proc->active = true;
            proc->eip = (uint32_t)entry_point;
            proc->esp = (uint32_t)alloc_page();
            proc->ebp = proc->esp;
            break;
        }
    }
    return proc;
}

void schedule() {
    // 1.proces
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].active) {
            // obnoveni stavu
            __asm__ (
                "mov %%esp, %0\n"
                "mov %%ebp, %1\n"
                :
                : "m" (processes[i].esp), "m" (processes[i].ebp)
            );
            return;
        }
    }
}
