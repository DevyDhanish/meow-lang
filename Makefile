CC := g++
PROJECT_NAME = meowlang
CPPFLAGS := -Wall -Wextra
EFLAGS := -c -g
INCLUDE_DIR := include
SRC_DIR := src
LIB_DIR := lib
OUTPUT_DIR := build

# LIB FILES
CORE_DIR = src/core
LEXER_DIR = src/lexer
TOKEN_DIR = src/token
DS = src/DS
PARSER_DIR = src/parser

Lib:
	$(CC) $(CPPFLAGS) $(EFLAGS) $(CORE_DIR)/*.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/core.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(LEXER_DIR)/*.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/lexer.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(TOKEN_DIR)/*.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/token.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(DS)/*.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/DS.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(PARSER_DIR)/*.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/parser.o
	ar rcs $(LIB_DIR)/libmeow.a $(LIB_DIR)/*.o

Bin:
	$(CC) $(CPPFLAGS) $(SRC_DIR)/*.cpp -I$(INCLUDE_DIR) -L$(LIB_DIR) -lmeow -o $(OUTPUT_DIR)/$(PROJECT_NAME)

Run:
	./build/meowlang example/main.meow
