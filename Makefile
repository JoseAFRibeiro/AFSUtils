CC = gcc
CFLAGS_DEBUG = -g -I ./include -O0 -Wall -march=native -std=c17 -Ddebug

SRC = $(wildcard ./src/*.c)
OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(SRC))

debug: $(OBJ)
	$(CC) $^ -o ./bin/main_debug.exe -lm

./obj/%.o: ./src/%.c
	$(CC) $(CFLAGS_DEBUG) -c -o $@ $<