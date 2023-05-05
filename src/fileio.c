#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

unsigned int getFileSize(FILE *f)
{
    int result;
    long fsize;

    result = fseek(f, 0, SEEK_END);

    if(result != 0)
        return 0;
    
    fsize = ftell(f);

    if(fsize > INT_MAX)
        return 0;

    return (int) fsize;
}

FILE * readFile(const char *source, int *fsize)
{
    off_t size;


    FILE *f = fopen(source, "rb");

    if(f == NULL)
    {
        printf("Error opening file\n");
        
        return NULL;    
    }

    fseeko64(f, 0, SEEK_END);
    size = ftello64(f);
    
   if(errno == -1L)
    {
        printf("Error determining file size\n");
        fclose(f);
        return NULL;    
    }

    rewind(f);
    *fsize = size;
    return f;
    
}
