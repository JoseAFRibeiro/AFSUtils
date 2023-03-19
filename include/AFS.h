#ifndef AFS_H_
#define AFS_H_

#define AFS_ARCHIVE_STRUCT_SIZE 0x08
#define AFS_ARCHIVE_STRUCT_OFFSET 0x08
#define AFS_SIZE_DWORD 4 * sizeof(char)

#include <stdio.h>

FILE * readFile(const char *source, int *fsize);
int writeFile(const char *destination, const char *buffer);

struct afs_entry{
    unsigned long size;
    unsigned long offset;
};

struct afs_archive{

    unsigned int numFiles;
    struct afs_entry *entryInfo; 
};

#endif 