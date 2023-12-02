all:
	g++ -g -c meowlang/src/core.cpp -Iinclude/ -o lib/core.o
	g++ -g -c meowlang/src/lexer.cpp -Iinclude/ -o lib/lexer.o
	g++ -g -c meowlang/src/token.cpp -Iinclude/ -o lib/token.o
	g++ -g -c parser/parser.cpp -Iinclude/ -o lib/parser.o

	ar rcs lib/libmeow.a lib/*.o

	g++ -g meowlang/main.cpp -Iinclude/ -Llib/ -lmeow