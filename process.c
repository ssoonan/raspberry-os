#include "process.h"


static struct Process process_table[NUM_PROCESS];
static int pid_num = 1;

void init_process()
{
  for (int i=0; i<NUM_PROCESS; i++) {
    struct Process *process = &process_table[i];
    process->state = PROC_INIT;

  }
}

void allocate_process(char* filename)
{

}