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

create_lib:
	$(CC) $(CPPFLAGS) $(EFLAGS) $(CORE_DIR)/*.cpp -I$(INCLUDE_DIR) -o $(LIB_DIR)/core.o
	ar rcs $(LIB_DIR)/libmeow.a $(LIB_DIR)/*.o

create_bin:
	$(CC) $(CPPFLAGS) $(SRC_DIR)/*.cpp -I$(INCLUDE_DIR) -L$(LIB_DIR) -lmeow -o $(OUTPUT_DIR)/$(PROJECT_NAME)

exe:
	./$(OUTPUT_DIR)/$(PROJECT_NAME) ../exampleProg/main.meow
