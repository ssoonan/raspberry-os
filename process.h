#include "stdint.h"

struct Process
{
  int pid;
  int state;
  uint64_t page_map;
};

void init_process();

#define STACK_SIZE (2 * 1024 * 1024)
#define NUM_PROCESS 100
#define PROC_UNUSED 0
#define PROC_INIT 1
#define PROC_RUNNING 2
#define PROC_READY 3