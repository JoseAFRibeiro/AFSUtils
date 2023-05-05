#ifndef AFS_H_
#define AFS_H_

#define AFS_ARCHIVE_STRUCT_SIZE 0x08
#define AFS_ARCHIVE_STRUCT_OFFSET 0x08
#define AFS_SIZE_DWORD 4 * sizeof(char)
#define AFS_BODY_START 0x800000

#include <stdio.h>

FILE * readFile(const char *source, int *fsize);
int writeFile(const char *destination, const char *buffer);
unsigned int getFileSize(FILE *f);


struct afs_entry{
    unsigned int offset;
    unsigned int size;
};

struct afs_archive{
    unsigned int numFiles;
    struct afs_entry *entryInfo; 
};

struct afs_archival_entry{
    FILE *f;
    unsigned int size;
    unsigned int offset;
};

struct afs_archive libafs_readAFSFile(const char *filepath);
struct afs_archive readAFSFile(const char *inputPath);

#endif 