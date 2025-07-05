# File Reverser (x86_64 Linux, NASM)

## Description
This program reverses the contents of a regular file in-place using Linux system calls and memory mapping. It is written in x86_64 assembly (NASM syntax) and interacts directly with the Linux kernel.

## Compilation
```bash
nasm -f elf64 -w+all -w+error -w-unknown-warning -w-reloc-rel -o freverse.o freverse.asm
ld --fatal-warnings -o freverse freverse.o
```

## Usage
```bash
./freverse <filename>
```