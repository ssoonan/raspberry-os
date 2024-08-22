#include "uart.h"
#include "print.h"
#include "debug.h"
#include "lib.h"
#include "handler.h"
#include "memory.h"

void KMain(void)
{
    init_uart();
    printk("Hello, Raspberry pi\r\n");
    printk("We are at EL %u\r\n", (uint64_t)get_el());

    init_memory();
    init_timer();
    init_interrupt_controller();
    enable_irq();

    while (1) {
        ;
    }
}