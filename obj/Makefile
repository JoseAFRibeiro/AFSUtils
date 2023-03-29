CC = gcc
CFLAGS_DEBUG = -g -I ../include -O0 -Wall -march=native -std=c17 -Ddebug -m64
CFLAGS_RELEASE = -I ../include -O2 -Wall -march=native -std=c17 -m64
ARCHIVER = ar
AR_FLAGS = -r

#-Warray-bounds=2 -Dlinux -fstack-protector-strong -fsanitize=address -fsanitize=undefined

SRC = $(wildcard ../src/*.c)
OBJ = $(patsubst ../src/%.c, %.o, $(SRC))

debug: $(SRC)
	$(CC) $^ -c $(CFLAGS_DEBUG)

release: $(SRC)
	$(CC) $^ -c $(CFLAGS_RELEASE)

archive: 
	$(AR) $(AR_FLAGS) ../bin/afslib.a $(notdir $(OBJ))
	

clean: 
	del $(OBJ)