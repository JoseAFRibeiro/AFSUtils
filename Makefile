CC = gcc
ARCHIVER = ar
AR_FLAGS = rci

SRC = $(wildcard ./src/*.c)
OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(SRC))

afsutil_release: 
	$(MAKE)  -C ./obj/ release
	$(CC) $(OBJ) -o afsutil.exe -lm

afsutil_debug: 
	$(MAKE) -C ./obj/. debug
	$(CC) $(OBJ) -o afsutil_debug.exe -lm

lib_debug: 
	$(MAKE) -C ./obj/. debug
	$(AR) $(AR_FLAGS) afslib_debug.a $(OBJ)
	
lib_release: 
	$(MAKE)  -C ./obj/ release
	$(AR) $(AR_FLAGS) afslib.a $(OBJ)

clean: $(OBJ)
	$(MAKE)  -C ./obj/ clean
	del ./bin/*.exe
	del ./bin/*.a


