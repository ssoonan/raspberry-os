#include "process.h"
#include "memory.h"
#include "debug.h"
#include "stddef.h"

static struct Process process_table[NUM_PROC];
static int pid_num = 1;
void pstart(struct TrapFrame *tf);
static struct LinkedList run_queue;
static struct Process *current_process;

static struct Process *find_unused_process(void)
{
    struct Process *process = NULL;

    for (int i = 0; i < NUM_PROC; i++)
    {
        if (process_table[i].state == PROC_UNUSED)
        {
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

static struct Process *alloc_new_process(void)
{
    struct Process *process;

    process = find_unused_process();
    ASSERT(process == &process_table[1]);

    process->stack = (uint64_t)kalloc();
    ASSERT(process->stack != 0);

    memset((void *)process->stack, 0, PAGE_SIZE);

    process->state = PROC_INIT;
    process->pid = pid_num++;

    process->tf = (struct TrapFrame *)(process->stack + PAGE_SIZE - sizeof(struct TrapFrame));
    process->tf->elr = 0x40000;
    process->tf->sp0 = 0x400000 + PAGE_SIZE;
    process->tf->spsr = 0;

    process->page_map = (uint64_t)kalloc();
    ASSERT(process->page_map != 0);

    memset((void *)process->page_map, 0, PAGE_SIZE);

    return process;
}

static void init_user_process(void)
{
    struct Process *process;

    process = alloc_new_process();
    ASSERT(process != NULL);

    ASSERT(setup_uvm((uint64_t)process->page_map, "INIT.BIN"));
    current_process = process;
    append_list_tail(&run_queue, (struct Node *)process);
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

void switch_process(struct Process *prev, struct Process *current)
{
    switch_vm(current->page_map);
    swap(prev->context, current->context);
}

void schedule()
{
    struct Node *head = remove_list_head(&run_queue);
    if (head == NULL)
    {
        // 런큐에 태스크가 X -> 현재 process 삽입
        append_list_tail(&run_queue, (struct Node *)&current_process);
        return;
    }
    struct Process *next_process = (struct Process *)head;
    next_process->state = PROC_RUNNING;
    switch_process(current_process, next_process);
}

void yield()
{
    if (is_list_empty(&run_queue))
    {
        // 태스크가 아예 없다면 idle 유지
        return;
    }
    // 현재 태스크 대기 & 맨 뒤로 넣기
    current_process->state = PROC_READY;
    append_list_tail(&run_queue, (struct Node *)&current_process);
    schedule();
}