#ifndef _LIB_H
#define _LIB_H

#include "stdint.h"
#include "stdbool.h"

struct Node
{
	struct Node *next;
};

struct LinkedList
{
	struct Node *head;
	struct Node *tail;
};

void delay(uint64_t value);
void out_word(uint64_t addr, uint32_t value);
uint32_t in_word(uint64_t addr);

void memset(void *dst, int value, unsigned int size);
void memcpy(void *dst, void *src, unsigned int size);
void memmove(void *dst, void *src, unsigned int size);
int memcmp(void *src1, void *src2, unsigned int size);
unsigned char get_el(void);

// 뒤에 추가
void append_list_tail(struct LinkedList *list, struct Node *item);
// 제일 앞을 삭제
struct Node *remove_list_head(struct LinkedList *list);
bool is_list_empty(struct LinkedList *list);
struct Node *remove_list(struct LinkedList *list, int wait);

#endif