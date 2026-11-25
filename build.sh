#!/bin/sh
# builds tvkey on c.h. ./build.sh 32: one i386 binary for 32 and 64-bit x86
set -e
cd "$(dirname "$0")"
[ "$1" = 32 ] && M32="-m32 -msse2"
${CC:-cc} -std=gnu11 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-empty-body -Wno-missing-field-initializers -Wno-deprecated-non-prototype $M32 -static -nostdlib -ffreestanding -fno-builtin \
    -fno-stack-protector -fno-asynchronous-unwind-tables -fno-pie -ffunction-sections -fdata-sections -fuse-ld=lld \
    -Wl,--gc-sections -Wl,-s -Wl,-z,norelro -o tvkey tvkey.c
