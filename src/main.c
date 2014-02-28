//This is the entry point for the kernel

#include "monitor.h"
#include "descriptor_tables.h"
#include "paging.h"
#include "kheap.h"
#include "multiboot.h"

int main(struct multiboot* mboot_ptr){
	init_descriptor_tables();
	vga_clear();
	vga_puts("Attempting page initialization...\n");
	
	unsigned int lol = kmalloc(8);

	initialize_paging();

	vga_puts("Testing kmalloc()\n");
	unsigned int a = kmalloc(8);
	unsigned int b = kmalloc(8);
	unsigned int c = kmalloc(8);
	vga_puts_hex(a);
	vga_putc('\n');
	vga_puts_hex(b);
	vga_putc('\n');
	vga_puts_hex(c);
	vga_puts("\nAttempting to free...\n");

	kfree(b);
	b = kmalloc(8);

	vga_puts_hex(b);

	vga_puts("\nChecking for initramfs...\n");
	
	ASSERT(mboot_ptr->mods_count != 0);

	vga_puts_hex(mboot_ptr->mods_addr);

	return 420;
}
