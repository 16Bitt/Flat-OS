static void main(){
	unsigned int vga = 0xB8000;
	*((char*) vga) = '?';
	return;
}
