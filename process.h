#ifndef _PROCESS_H
#define _PROCESS_H

#include "handler.h"
#include "file.h"
#include "lib.h"

struct Process
{
  struct Node *node;
  int pid;
  int state;
  uint64_t page_map;
  uint64_t stack;
  struct TrapFrame *tf;
  uint64_t context;
  int wait;
  struct FileDesc *file[100];

};

#define STACK_SIZE (2 * 1024 * 1024)
#define NUM_PROC 10
#define PROC_UNUSED 0
#define PROC_INIT 1
#define PROC_RUNNING 2
#define PROC_READY 3
#define PROC_SLEEP 4
#define PROC_KILLED 5

void init_process(void);
void swap(uint64_t *prev, uint64_t next);
void schedule();
void trap_return(void);
struct Process *get_current_pc(void);
void yield();
void sleep(int wait);
void wake_up(int wait);
void exit(void);
void wait(int pid);

#endif