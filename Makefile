cook:
	gcc main.c -Wall -Wextra -o Meow

all:
	make cook && make run

run:
	./Meow main.meow
