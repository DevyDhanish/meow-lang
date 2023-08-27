# [Meow Lang]

I might finish this idk, here are all the details if you want to contribute

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

# BUILD DEV (very early stages)

# GETTING STARTED
currently the program cannot compile it can only show the generated tokens
if you want to run the program then follow these steps.

# Caution
I use ubuntu, this steps might not work on windows or mac systems.

`fork this repo`
`git clone https://github.com/<your-user-name>/meow-lang`
`cd build`
`cmake ../`
`make`
`./meow ../example/main.meow`

# Prerequisites
`cmake`
`nasm` my plan it to read the source file and generate the asm file then leave it up to nasm/masm or other assembler to turn the asm file to binary file
`gcc`