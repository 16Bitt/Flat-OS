#include "file.h"
#include "common.h"
#include "monitor.h"

unsigned int fopen(char* filename){
	if(!is_file(filename))
		return 0;

	return (unsigned int) get_file_data(filename);
}

int fexec_sp(char* filename){
	return -1;
}

void fprint(char* filename){
	if(!is_file(filename))
		return;

	unsigned int i;
	for(i = 0; i < get_file_size(filename); i++)
		vga_putc((char) get_file_data(filename)[i]);

	vga_putc('\n');
}
