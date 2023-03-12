#ifndef AFSIO_H_
#define AFSIO_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * readFile(const char *source, int *fsize);
int writeFile(const char *destination, const char *buffer);
int readAFSFile(const char *inputPath, const char *outputPath);

#endif 