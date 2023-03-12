#include "afsio.h"
#include "AFS.h"

static inline int readHeader(FILE *f, struct afs_archive *archive)
{
    unsigned char header[4];
    
    fread(header, sizeof(char), AFS_SIZE_DWORD, f);
    fseeko64(f, AFS_SIZE_DWORD, SEEK_SET);
     
    if(strcmp(header, "AFS\0"))
    {
        return -1;
    }
    
    return 0;
}
static inline int indexFiles();

int readAFSFile(const char *inputPath, const char *outputPath)
{
    int fileSize;
    struct afs_archive archive;

    FILE *f = readFile(inputPath, &fileSize);
    readHeader(f, &archive);

    return 0;
}