#ifndef _LIB_H_
#define _LIB_H_

#include "stdint.h"

int printf(const char *format, ...);
int writeu(char *buffer, int buffer_size);
void sleepu(uint64_t ticks);

#endif