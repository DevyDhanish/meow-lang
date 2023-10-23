CC := g++
PROJECT_NAME = meowlang
CPPFLAGS := -Wall -Wextra
EFLAGS := -c -g
INCLUDE_DIR := include
SRC_DIR := src
LIB_DIR := lib
OUTPUT_DIR := build

create:
	mkdir lib build

libs:
	$(CC) $(CPPFLAGS) $(EFLAGS) $(SRC_DIR)/core.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/core.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(SRC_DIR)/token.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/token.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(SRC_DIR)/lexer.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/lexer.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(SRC_DIR)/parser.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/parser.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(SRC_DIR)/tree.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/tree.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(SRC_DIR)/map.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/map.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(SRC_DIR)/interpreter.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/interpreter.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(SRC_DIR)/vm.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/vm.o
	$(CC) $(CPPFLAGS) $(EFLAGS) $(SRC_DIR)/error.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/error.o

	ar rcs $(LIB_DIR)/libmeow.a $(LIB_DIR)/*.o

bin-debug:
	$(CC) $(CPPFLAGS) -DDEBUG main.cpp -I$(INCLUDE_DIR) -L$(LIB_DIR) -lmeow -o $(OUTPUT_DIR)/$(PROJECT_NAME)
	
bin-release:
	$(CC) $(CPPFLAGS) main.cpp -I$(INCLUDE_DIR) -L$(LIB_DIR) -lmeow -o $(OUTPUT_DIR)/$(PROJECT_NAME)

clean:
	rm -r build
	rm -r lib
