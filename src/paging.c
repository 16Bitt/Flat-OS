#include "paging.h"
#include "kheap.h"
#include "monitor.h"
#include "isr.h"

unsigned int* frames;
unsigned int n_frames;

page_directory_t* kernel_dir = 0;
page_directory_t* current_dir = 0;

extern unsigned int placement_address;
extern heap_t* kheap;

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))
//#define PANIC(msg) vga_puts(msg); vga_puts(__FILE__); vga_puts_hex(__LINE__); for(;;) int nop;

static void set_frame(unsigned int frame_address){
	unsigned int frame = frame_address / 0x1000;
	unsigned int index = INDEX_FROM_BIT(frame);
	unsigned int offset = OFFSET_FROM_BIT(frame);
	
	frames[index] |= (1 << offset);
}

static void clear_frame(unsigned int frame_address){
	unsigned int frame = frame_address / 0x1000;
	unsigned int index = INDEX_FROM_BIT(frame);
	unsigned int offset = OFFSET_FROM_BIT(frame);

	frames[index] &= ~(1 << offset);
}

static unsigned int first_frame(){
	unsigned int i, j;
	for(i = 0; i < INDEX_FROM_BIT(n_frames); i++)
		if(frames[i] != 0xFFFFFFFF)
			for(j = 0; j < 32; j++){
				unsigned int test = 1 << j;
				if(!(frames[i] & test))
					return i * 4 * 8 + j;
			}
}

//^This is all bit moving stuff^

void alloc_frame(page_t* page, int is_kernel, int is_writeable){
	if(page->frame != 0){
		return;
	}
	
	else{
		unsigned int index = first_frame();
		
		if(index == (unsigned int) -1){
			PANIC("NO FRAMES AVAILABLE\n")

			vga_puts("PANIC IN FILE ");
			vga_puts(__FILE__);
			vga_puts("-- NO FRAMES AVAILABLE");

			int i;
			for(;;)
				i++;
		}

		set_frame(index * 0x1000);
		page->present = 1;
		page->rw = (is_writeable)? 1 : 0;
		page->user = (is_kernel)? 0 : 1;
		page->frame = index;
	}
}

void free_frame(page_t* page){
	unsigned int frame;
	
	if(!(frame = page->frame))
		return;

	clear_frame(frame);
	page->frame = 0;
}

void initialize_paging(){
	unsigned int mem_end_page = 0x10000000;
	
	n_frames = mem_end_page / 0x1000;
	frames = (u32int*) kmalloc(INDEX_FROM_BIT(n_frames));
	memset((void*) frames, 0, INDEX_FROM_BIT(n_frames));

	kernel_dir = (page_directory_t*) kmalloc_a(sizeof(page_directory_t));
	memset((void*) kernel_dir, 0, sizeof(page_directory_t));
	current_dir = kernel_dir;
	
	int i = 0;
	for(i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
		get_page(i, 1, kernel_dir);

	i = 0;
	while(i < placement_address + 0x1000){
		alloc_frame(get_page(i, 1, kernel_dir), 0, 0);
		i += 0x1000;
	}
	
	for(i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
		alloc_frame(get_page(i, 1, kernel_dir), 0, 0);

	register_interrupt_handler(14, page_fault);
	switch_page_dir(kernel_dir);

	kheap = create_heap(KHEAP_START, KHEAP_START + KHEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);
}

void switch_page_dir(page_directory_t* dir){
	current_dir = dir;
	asm volatile("mov %0, %%cr3"::"r"(&dir->tables_physical));
	unsigned int cr0;
	asm volatile("mov %%cr0, %0":"=r"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0"::"r"(cr0));
}

page_t* get_page(unsigned int address, int make, page_directory_t* dir){
	address /= 0x1000;
	unsigned int table_index = address / 1024;

	if(dir->tables[table_index])
		return &dir->tables[table_index]->pages[address % 1024];

	if(make){
		unsigned int tmp;
		dir->tables[table_index] = (page_table_t*) kmalloc_ap(sizeof(page_table_t), &tmp);
		memset((void*) dir->tables[table_index], 0, 0x1000);
		dir->tables_physical[table_index] = tmp | 0x7;
		return &dir->tables[table_index]->pages[address % 1024];
	}
	
	return 0;
}

void page_fault(registers_t regs){
	unsigned int fault_address;
	asm volatile("mov %%cr2, %0":"=r"(fault_address));

	int present = !(regs.err_code & 1);
	int rw = regs.err_code & 2;
	int user = regs.err_code & 4;
	int reserved = regs.err_code & 8;
	int execution = regs.err_code & 0x10;

	vga_puts("PAGE FAULT AT ");
	vga_puts_hex(fault_address);
	vga_puts(":\n");

	if(present) vga_puts("-PAGE ABSENT\n");
	if(rw) vga_puts("-READ ONLY\n");
	if(user) vga_puts("-IN USER MODE\n");
	if(reserved) vga_puts("-OVERWRITTEN RESERVED BITS IN PAGE\n");
	if(execution) vga_puts("-FAILED INSTRUCTION FETCH\n");
	
	PANIC("PAGE FAULT");
}
