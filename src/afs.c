#include "afsio.h"
#include "AFS.h"

static inline int readHeader(FILE *f)
{
    unsigned char header[4];

    if(f == NULL)
        return 1;
    
    fread(header, sizeof(char), AFS_SIZE_DWORD, f);
    fseeko64(f, AFS_SIZE_DWORD, SEEK_SET);
     
    if(strcmp(header, "AFS\0"))
    {
        return -1;
    }
    
    return 0;
}
static inline int indexFiles(FILE *f, struct afs_archive *archive)
{
    int result = 0;

    fread(&archive->numFiles, sizeof(int), 1, f);
    archive->entryInfo = malloc(sizeof(struct afs_entry) * archive->numFiles);
    
   for(int i = 0; i< archive->numFiles; i++)
        fread(&archive->entryInfo[i], AFS_ARCHIVE_STRUCT_SIZE, 1, f);

    return 0;
}

int readAFSFile(const char *inputPath, const char *outputPath)
{
    int fileSize;
    int result;
    struct afs_archive archive;

    FILE *f = readFile(inputPath, &fileSize);

    result = readHeader(f);
    if(result != 0)
        return -1;

    result = indexFiles(f, &archive);

    return 0;
}