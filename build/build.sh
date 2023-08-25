#!/bin/bash
./meow ../example/main.meow main.asm
nasm -f elf64 main.asm -o main.o
ld main.o -o main
./main
echo $?