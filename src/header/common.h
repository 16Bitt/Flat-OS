#ifndef COMMON_H
#define COMMON_H

//Define basic types for easier programming
typedef unsigned int u32int;
typedef int s32int;
typedef unsigned short u16int;
typedef short s16int;
typedef unsigned char u8int;
typedef char s8int;
typedef int size_t;

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);
void* memset(void* s, int c, size_t n);
void* memcpy(void* dest, const void* src, size_t n);

int strcmp(char* str1, char* str2);

void panic(char* msg, char* file, unsigned int line);

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void) 0 : panic("ASSERTION FAILED", __FILE__, __LINE__))

#endif
