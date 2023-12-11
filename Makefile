all:
	g++ -g -c meowlang/src/core.cpp -o lib/core.o
	g++ -g -c meowlang/src/lexer.cpp -o lib/lexer.o
	g++ -g -c meowlang/src/token.cpp -o lib/token.o
	g++ -g -c parser/parser.cpp -Iinclude/ -o lib/parser.o
	g++ -g -c meowlang/src/bytecode.cpp -o lib/code.o
	g++ -g -c meowlang/src/compiler.cpp -o lib/compiler.o
	g++ -g -c meowlang/src/internals/stackframe.cpp -o lib/stackframe.o
	g++ -g -c meowlang/src/vm.cpp -o lib/vm.o

	ar rcs lib/libmeow.a lib/*.o

	g++ -g meowlang/main.cpp -Iinclude/ -Llib/ -lmeow