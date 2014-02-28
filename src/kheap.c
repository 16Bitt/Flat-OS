#include "common.h"
#include "kheap.h"

extern unsigned int end;
unsigned int placement_address = (unsigned int) &end;


unsigned int kmalloc_control(unsigned int size, int alignment, unsigned int* physical){
	if((alignment == 1) && (placement_address & 0xFFFFF000)){
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000;
	}

	if(physical)
		*physical = placement_address;

	unsigned int ret = placement_address;
	placement_address += size;
	
	return ret;
}

unsigned int kmalloc_a(unsigned int size){
	return kmalloc_control(size, 1, 0);
}

unsigned int kmalloc_p(unsigned int size, unsigned int* physical){
	return kmalloc_control(size, 0, physical);
}

unsigned int kmalloc_ap(unsigned int size, unsigned int* physical){
	return kmalloc_control(size, 1, physical);
}

unsigned int kmalloc(unsigned int size){
	return kmalloc_control(size, 0, 0);
}

void kfree(void* p){
	asm volatile("nop");
}
