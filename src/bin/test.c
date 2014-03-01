static char qm;

static void main(){
	char qm = '?';
	unsigned int vga = 0xB8000;
	*((char*) vga) = qm;
	return;
}

static char qm = '?';
