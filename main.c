#include "uart.h"
#include "print.h"
#include "debug.h"
#include "lib.h"

void KMain(void)
{
    init_uart();
    printk("Hello, Raspberry pi\r\n");
    printk("We are at EL %u\r\n", (uint64_t)get_el());

    char *p = (char*)0xffff000000000000;
    *p = 1;

    printk("This message shouldn't be printed\r\n");
    
    while (1) {
        ;
    }
}