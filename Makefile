CC = gcc
ARCHIVER = ar
AR_FLAGS = -rciv

SRC = $(wildcard ./src/*.c)
OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(SRC))

afsutil_release: 
	$(MAKE)  -C ./obj/ release
	$(CC) $(OBJ) -o ./bin/afsutil.exe -lm

afsutil_debug: 
	$(MAKE) -C ./obj/. debug
	$(CC) $(OBJ) -o ./bin/afsutil_debug.exe -lm

lib_debug: 
	$(MAKE) -C ./obj/. debug
	$(AR) $(AR_FLAGS) ./bin/afslib_debug.a ./obj/*.o
	
lib_release: 
	$(MAKE)  -C ./obj/ release
	$(AR) $(AR_FLAGS) ./bin/afslib.a ./obj/*.o

clean: $(OBJ)
	$(MAKE)  -C ./obj/ clean
	del ./bin/*.exe
	del ./bin/*.a


