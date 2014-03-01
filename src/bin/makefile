SOURCES=test.o
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Iheader/ -fpic -nostartfiles
LDFLAGS=-Tlink.ld -melf_i386 -shared -fpie
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o

link:
	ld $(LDFLAGS) -o test $(SOURCES)
