#ifndef KHEAP_H
#define KHEAP_H

#include "common.h"
#include "ordered_array.h"

unsigned int kmalloc_a(unsigned int size);
unsigned int kmalloc_p(unsigned int size, unsigned int* physical);
unsigned int kmalloc_ap(unsigned int size, unsigned int* physical);
unsigned int kmalloc(unsigned int size);

#define KHEAP_START 0xC0000000
#define KHEAP_INITIAL_SIZE 0x100000
#define HEAP_INDEX_SIZE 0x20000
#define HEAP_MAGIC 0x69694208
#define HEAP_MIN_SIZE 0x70000

typedef struct{
	unsigned int magic;
	unsigned char is_hole;
	unsigned int size;
} header_t;

typedef struct{
	unsigned int magic;
	header_t* header;
} footer_t;

typedef struct{
	ordered_array_t index;
	unsigned int start_address;
	unsigned int end_address;
	unsigned int max_address;
	unsigned char supervisor;
	unsigned char readonly;
} heap_t;

heap_t* create_heap(unsigned int start, unsigned int end, unsigned int max, unsigned char supervisor, unsigned char readonly);

void* alloc(unsigned int size, unsigned char page_align, heap_t* heap);
void free(void* ptr, heap_t* heap);

#endif
