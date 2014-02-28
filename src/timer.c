#include "timer.h"
#include "isr.h"
#include "monitor.h"

unsigned int tick = 0;

static void timer_callback(registers_t regs){
	tick++;
	vga_puts("TICK:");
	vga_puts_hex(tick);
	vga_putc('\n');
}

void init_timer(unsigned int frequency){
	register_interrupt_handler(32, &timer_callback);
	u32int divisor = 1193180/frequency;

	outb(0x43, 0x36);

	unsigned char low = (unsigned char) (divisor & 0xFF);
	unsigned char high = (unsigned char) ((divisor >> 8) & 0xFF);

	outb(0x40, low);
	outb(0x40, high);
}
