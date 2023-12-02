all:
	g++ -g -c include/internals/list/list.cpp -o lib/list.o
	g++ -g -c meowlang/src/internals/display_ast.cpp -o lib/disast.o
	g++ -g -c meowlang/src/core.cpp -o lib/core.o
	g++ -g -c meowlang/src/lexer.cpp -o lib/lexer.o
	g++ -g -c meowlang/src/token.cpp -o lib/token.o
	g++ -g -c parser/parser.cpp -Iinclude/ -o lib/parser.o

	ar rcs lib/libmeow.a lib/*.o

	g++ -g meowlang/main.cpp -Iinclude/ -Llib/ -lmeow