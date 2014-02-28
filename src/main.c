//This is the entry point for the kernel

#include "monitor.h"
#include "descriptor_tables.h"
#include "kheap.h"
#include "multiboot.h"
#include "fs.h"
#include "file.h"

int main(struct multiboot* mboot_ptr){
	vga_clear();

	vga_puts("Setting up descriptor tables...\n");
	init_descriptor_tables();
	
	vga_puts("Checking for initramfs...\n");
	ASSERT(mboot_ptr->mods_count != 0);
	mnt_initrd(mboot_ptr->mods_addr);
	
	fprint("test.txt");

	return 420;
}
