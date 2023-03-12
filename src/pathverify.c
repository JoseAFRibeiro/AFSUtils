#include <sys/stat.h>

int isPath(const char *path)
{
    struct stat dirInfo;

    if(!stat( path, &dirInfo))
        return 1;
    else
        return 0;
}

