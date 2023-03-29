CC = gcc
ARCHIVER = ar
AR_FLAGS = rciv

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
	$(MAKE) -C ./obj/. archive

	
lib_release: 
	$(MAKE)  -C ./obj/ release
	$(MAKE) -C ./obj/. archive

clean: $(OBJ)
	$(MAKE)  -C ./obj/ clean
	del ./bin/*.exe
	del ./bin/*.a


