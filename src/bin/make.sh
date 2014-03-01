#!/usr/bin/env bash

echo "Compiling..."
gcc -S -fpic -m32 -nostdinc -fno-builtin -fno-stack-protector -ffreestanding -nostartfiles $1.c
echo "Fixing file..."
./fix.rb $1.s $1.fs
echo "Assembling..."
gcc -m32 -nostdinc -fno-builtin -fno-stack-protector -ffreestanding -fpic -nostartfiles -c -o $1.o -xassembler $1.fs
echo "Linking..."
ld -Tlink.ld -melf_i386 -shared -o $1 $1.o
echo "Success."
