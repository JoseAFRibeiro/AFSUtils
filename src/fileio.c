#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


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
    
   /* if(errno == -1L)
    {
        printf("Error determining file size\n");
        fclose(f);
        return NULL;    
    }*/

    rewind(f);
    *fsize = size;
    return f;
    
}
