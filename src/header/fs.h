#ifndef FS_H
#define FS_H

#define FFS_MAGIC 0x04206969
#define FFS_ENTRY_SIZE (128 + 4 + 4)

typedef struct file{
	unsigned int	offset,
			size;
	char* 		name;
	unsigned char* 	data;
} file_t;

typedef struct directory{
	unsigned int 	start,
			num_files;
	file_t** files;
} directory_t;

extern directory_t* fs_root;
extern unsigned int size;

void mnt_initrd(unsigned int address);
int is_file(char* name);
unsigned int get_file_size(char* name);
unsigned char* get_file_data(char* name);
#endif
