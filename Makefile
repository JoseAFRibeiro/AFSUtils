CC = gcc
ARCHIVER = ar
CFLAGS_DEBUG = -g -I ./include -O0 -Wall -march=native -std=c17 -Ddebug 
#-Warray-bounds=2 -Dlinux -fstack-protector-strong -fsanitize=address -fsanitize=undefined

SRC = $(wildcard ./src/*.c)
OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(SRC))

debug: $(OBJ)
	$(CC) $^ -o ./bin/main_debug.exe -lm 

lib: $(OBJ)
#	$(filter-out main.o, $(OBJ))
	rm ./obj/main.o
	$(ARCHIVER) rcs ./bin/afsutil.a ./obj/afs.o ./obj/fileio.o ./obj/libafs.o ./obj/pathverify.o

clean: $(OBJ)
	rm $^
	debug

./obj/%.o: ./src/%.c
	$(CC) -c -o $@ $< $(CFLAGS_DEBUG)

