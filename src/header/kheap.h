#ifndef KHEAP_H
#define KHEAP_H

#include "common.h"

unsigned int kmalloc_a(unsigned int size);
unsigned int kmalloc_p(unsigned int size, unsigned int* physical);
unsigned int kmalloc_ap(unsigned int size, unsigned int* physical);
unsigned int kmalloc(unsigned int size);
void kfree(void* ptr);

#define KHEAP_START 0xC0000000
#define KHEAP_INITIAL_SIZE 0x100000
#define HEAP_INDEX_SIZE 0x20000
#define HEAP_MAGIC 0x69694208
#define HEAP_MIN_SIZE 0x70000

#endif
