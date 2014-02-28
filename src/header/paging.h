#ifndef PAGING_H
#define PAGING_H

#include "common.h"
#include "isr.h"

typedef struct page{
	unsigned int present 	: 1;
	unsigned int rw 	: 1;
	unsigned int user 	: 1;
	unsigned int accessed 	: 1;
	unsigned int dirty 	: 1;
	unsigned int unused 	: 7;
	unsigned int frame 	: 20;
} page_t;

typedef struct page_table{
	page_t pages[1024];
} page_table_t;

typedef struct page_directory{
	page_table_t* tables[1024];
	unsigned int tables_physical[1024];
	unsigned int physical_address;
} page_directory_t;

void initialize_paging();
void switch_page_dir(page_directory_t* new_dir);
page_t* get_page(unsigned int address, int make, page_directory_t* dir);
void page_fault(registers_t regs);

#endif
