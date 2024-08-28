#include "process.h"
#include "memory.h"
#include "debug.h"
#include "stddef.h"

static struct Process process_table[NUM_PROC];
static int pid_num = 1;
void pstart(struct TrapFrame *tf);

static struct Process* find_unused_process(void)
{
    struct Process *process = NULL;

    for (int i = 0; i < NUM_PROC; i++) {
        if (process_table[i].state == PROC_UNUSED) {
            process = &process_table[i];
            break;
        }
    }

    return process;
}


static void init_idle_process(void)
{
    struct Process *process;

    process = find_unused_process();
    ASSERT(process == &process_table[0]);

    process->state = PROC_RUNNING;
    process->pid = 0;
    process->page_map = P2V(read_pgd());
}

static struct Process* alloc_new_process(void)
{
    struct Process *process;

    process = find_unused_process();
    ASSERT(process == &process_table[1]);

    process->stack = (uint64_t)kalloc();
    ASSERT(process->stack != 0);

    memset((void*)process->stack, 0, PAGE_SIZE);

    process->state = PROC_INIT;
    process->pid = pid_num++;

    process->tf = (struct TrapFrame*)(process->stack + PAGE_SIZE - sizeof(struct TrapFrame));
    process->tf->elr = 0x400000;
    process->tf->sp0 = 0x400000 + PAGE_SIZE;
    process->tf->spsr = 0;

    process->page_map = (uint64_t)kalloc();
    ASSERT(process->page_map != 0);

    memset((void*)process->page_map, 0, PAGE_SIZE);

    return process;
}

static void init_user_process(void)
{
    struct Process *process;

    process = alloc_new_process();
    ASSERT(process != NULL);

    ASSERT(setup_uvm((uint64_t)process->page_map, "INIT.BIN"));
}

void launch(void)
{
    switch_vm(process_table[1].page_map);
    pstart(process_table[1].tf);
}

void init_process(void)
{
    init_idle_process();
    init_user_process();

    launch();
}