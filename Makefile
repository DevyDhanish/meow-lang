CC = gcc

PROJECT_NAME := meowlang

OUTPUT_FILE := build
LIBS_DIR := libs

CFLAGS := -Wall -Wextra

CORE_FILE 	:= src/core/core.c
TOKEN_FILE 	:= src/token/tokendef.c 
LEXER_FILE 	:= src/lexer/lexer.c 
LIST_FILES 	:= src/DS/list.c 
DICT_FILES  := src/DS/dict.c 
TREE_FILES  := src/DS/tree.c
AST_FILES 	:= src/AST_GEN/ast_gen.c

create_libs:
	$(CC) -c $(CORE_FILE) $(CFLAGS) -o $(LIBS_DIR)/core.o
	$(CC) -c $(TOKEN_FILE) $(CFLAGS) -o $(LIBS_DIR)/token.o
	$(CC) -c $(LEXER_FILE) $(CFLAGS) -o $(LIBS_DIR)/lexer.o 
	$(CC) -c $(LIST_FILES)  $(CFLAGS) -o $(LIBS_DIR)/list.o
	$(CC) -c $(DICT_FILES)  $(CFLAGS) -o $(LIBS_DIR)/dict.o
	$(CC) -c $(TREE_FILES)  $(CFLAGS) -o $(LIBS_DIR)/tree.o
	$(CC) -c $(AST_FILES) $(CFLAGS) -o $(LIBS_DIR)/ast_gen.o

	ar rcs $(LIBS_DIR)/libmeow.a $(LIBS_DIR)/*.o

	echo "Sucessfully generated the libmeow.a files in libs/libmeow.a"

create_main:
	$(CC) $(CFLAGS) src/meow.c -L$(LIBS_DIR) -lmeow -o $(OUTPUT_FILE)/$(PROJECT_NAME)

execute:
	./$(OUTPUT_FILE)/$(PROJECT_NAME) ./example/main.meow