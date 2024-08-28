#include "syscall.h"
#include "print.h"
#include "debug.h"
#include "stddef.h"

static SYSTEMCALL system_calls[10];

static int sys_write(int64_t *argptr)
{
    write_console((char*)argptr[0], (int)argptr[1]);
    return (int)argptr[1];
}

void system_call(struct TrapFrame *tf)
{
    int64_t i = tf->x8;
    int64_t param_count = tf->x0;
    int64_t *argptr = (int64_t*)tf->x1;

    if (param_count < 0 || i != 0) {
        tf->x0 = -1;
        return;
    }

    tf->x0 = system_calls[i](argptr);
}

void init_system_call(void)
{
    system_calls[0] = sys_write;
}
