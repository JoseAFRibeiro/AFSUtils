#include "afsio.h"
#include "AFS.h"

static inline int readHeader(FILE *f, struct afs_archive *archive)
{
    char header[4];
    
    fread(header, 4 * sizeof(char), 4 * sizeof(char), f);
    fseeko64(f, AFS_SIZE_DWORD, SEEK_SET);
     
    if(strcmp(header, "AFS\0"))
    {
        return -1;
    }

    fread(&archive->numFiles, AFS_SIZE_DWORD * sizeof (char), 1, f);
    archive->entryInfo = malloc(sizeof(struct afs_entry) * archive->numFiles);

    for(int i = 0; i< archive->numFiles; i++)
        fread(&archive->entryInfo[i], AFS_ARCHIVE_STRUCT_SIZE, 1, f);

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