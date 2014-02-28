#!/usr/bin/env bash

qemu-system-x86_64 -kernel build/kernel -initrd initramfs/initrd -monitor stdio
