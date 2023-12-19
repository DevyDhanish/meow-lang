UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
TARGET := meowlang_linux 
else
TARGET := meowlang.exe
endif

all:
	g++ -g -c meowlang/src/bltins/bltins.cpp -o lib/bltins.o
	g++ -g -c meowlang/src/core.cpp -o lib/core.o
	g++ -g -c meowlang/src/lexer.cpp -o lib/lexer.o
	g++ -g -c meowlang/src/token.cpp -o lib/token.o
	g++ -g -c parser/parser.cpp -Iinclude/ -o lib/parser.o
	g++ -g -c meowlang/src/bytecode.cpp -o lib/code.o
	g++ -g -c meowlang/src/compiler.cpp -o lib/compiler.o
	g++ -g -c meowlang/src/internals/stackframe.cpp -o lib/stackframe.o
	g++ -g -c meowlang/src/vm.cpp -o lib/vm.o
	g++ -g -c meowlang/src/internals/meow_objects.cpp -o lib/meowobj.o
	g++ -g -c meowlang/src/internals/constants.cpp -o lib/constants.o
	ar rcs lib/libmeow.a lib/*.o

	g++ -g meowlang/main.cpp -Iinclude/ -Llib/ -lmeow -o $(TARGET)