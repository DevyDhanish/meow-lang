![Meow gif](./Meow.gif)

# [Meow Lang]

I might finish this idk, here are all the details if you want to contribute

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

# BUILD DEV (very early stages)

# GETTING STARTED
currently the program cannot compile it can only show the generated tokens<br />
if you want to run the program then follow these steps.

# Caution
I use ubuntu, this steps might not work on windows or mac systems.

`fork this repo`<br />
`git clone https://github.com/<your-user-name>/meow-lang`<br />
`mkdir build`<br />
`mkdir libs`<br />
`make create_libs`<br />
`make create_main`<br />
`cd build`<br />
`./meowlang ../example/main.meow`<br />

# Prerequisites
1 - `make` <br />
2 - `nasm` my plan it to read the source file and generate the assembly file according to the system it's compiling on then leave it up to nasm/masm or other assembler to turn the asm file to binary file <br />
3 - `gcc` <br />

# PLAN
step 1 - Put the whole file in buffer so it is easier to work with.
step 2 - Lexer will work with this buffer to produce tokens
step 3 - read the tokenized list and generate a AST and check of syntax errors
step 4 - read the AST and generate code according to it


# TODO
[ DONE ] - Read the whole file and put it into buffer for easy operations <br />
[ DONE ] - Read the buffer and tokenize it <br />
[ PARTIALLY DONE ] - Write all the tokes<br />
[ DONE ] - Make a tree structure for the AST (Abstract syntax tree)<br />
[ ] - Make a parser thats read the tokenized list and generates a AST <br />
[ ] - Syntax check and all <br />
[ ] - traverse the AST and generate the equivalent asm code <br />
