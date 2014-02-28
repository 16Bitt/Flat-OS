#ifndef FILE_H
#define FILE_H

#include "common.h"
#include "fs.h"

unsigned int fopen(char* filename);
int fexec_sp(char* filename);

void fprint(char* filename);

#endif
