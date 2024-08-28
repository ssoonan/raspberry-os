#ifndef _LIB_H_
#define _LIB_H_

#include "stdint.h"

int printf(const char *format, ...);
int writeu(char *buffer, int buffer_size);
void sleepu(uint64_t ticks);
int open_file(char *name);
void close_file(int fd);
int get_file_size(int fd);


#endif