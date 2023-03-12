CC = gcc
CFLAGS_DEBUG = -g -I ./include -O0 -Wall  -march=native -std=c17 -Ddebug 
#-Warray-bounds=2 -Dlinux -fstack-protector-strong -fsanitize=address -fsanitize=undefined 

SRC = $(wildcard ./src/*.c)
OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(SRC))

debug: $(OBJ)
	$(CC) $^ -o ./bin/main_debug.exe -lm 

./obj/%.o: ./src/%.c
	$(CC) -c -o $@ $< $(CFLAGS_DEBUG)