SOURCES=boot.o main.o common.o monitor.o interrupt.o descriptor_tables.o isr.o table.o timer.o kheap.o paging.o ordered_map.o
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Iheader/ 
LDFLAGS=-Tlink.ld -melf_i386
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o build/kernel

link:
	ld $(LDFLAGS) -o build/kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
