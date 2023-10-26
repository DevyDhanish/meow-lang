![Meow gif](./Meow.gif)

# [Meow Lang]

I might finish this idk, here are all the details if you want to contribute. And I know this code is ugly as fuck i'm going to fix it, I think.

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

# BUILD v1.6.11 (First Version)

# GETTING STARTED

# ❗❗Caution❗❗
I use ubuntu, this steps might not work on windows or mac systems.

`fork this repo`<br />
`git clone https://github.com/<your-user-name>/meow-lang`<br />
`make create`<br />
`make libs`<br />
`make bin-debug` with debug info<br />
`make bin-release` without debug info<br />
`cd build`<br />
`./meowlang main.meow`<br />

# Prerequisites
1 - `make/mingw32-make` <br />
3 - `g++/clang++` <br />

# PLAN
step 1 - Put the whole file in buffer so it is easier to work with.<br>
step 2 - Lexer will work with this buffer to produce tokens<br>
step 3 - read the tokenized list and generate a AST and check of syntax errors<br>
step 4 - read the AST and genered bytecode according to it<br>
step 5 - read the bytecode and execute it <br>


# TODO📋
[ PARTIALLY DONE ] - Read the whole file and put it into buffer for easy operations <br />
[ PARTIALLY DONE ] - Read the buffer and tokenize it <br />
[ PARTIALLY DONE ] - Write all the tokes<br />
[ PARTIALLY DONE ] - Make a tree structure for the AST (Abstract syntax tree)<br />
[ PARTIALLY DONE ] - Make a parser thats read the tokenized list and generates a AST <br />
[ PARTIALLY DONE ] - Syntax check and all <br />
[ PARTIALLY DONE ] - traverse the AST and execute it <br />
