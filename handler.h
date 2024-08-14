
#ifndef _HANDLER_H
#define _HANDLER_H
#include "stdint.h"

void enable_timer(void);
uint32_t check_timer_status(void);
void set_timer_interval(uint32_t value);
uint32_t read_timer_freq(void);
void init_timer(void);
void enable_irq(void);

#endif