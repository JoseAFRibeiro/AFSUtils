#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "afsio.h"
#include "AFS.h"

static FILE *origin;
static char *originalFName;
static int originalFNameSize;


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
    {
        fread(&archive->entryInfo[i].offset, AFS_SIZE_DWORD, 1, f);
        fread(&archive->entryInfo[i].size, AFS_SIZE_DWORD, 1, f);

    }
    return 0;
}

static inline struct afs_archive readAFSFile(const char *inputPath)
{
    int fileSize;
    int result;
    int fnamesize;
    struct afs_archive archive;

    int namelen = strlen(inputPath);
    int cursor = namelen;
    originalFName = malloc(namelen);

    if(originalFName == NULL)
    {
        struct afs_archive err = {0};
        return err;
    }

    while(inputPath[cursor] != '/')
    {
        cursor --;
    }

    fnamesize = originalFNameSize = namelen - cursor;

    memcpy(originalFName, &inputPath[cursor],  originalFNameSize);

    FILE *f = readFile(inputPath, &fileSize);
    
    result = readHeader(f);

    if(result != 0)
    {
        struct afs_archive err = {0};
        return err;
    }

    result = indexFiles(f, &archive);
    origin = f;
    return archive;
}

static inline int serializeOut(const char *outpath, struct afs_archive archive)
{
    FILE *f;
    char *buffer;
    char *fname;
    unsigned char fnamesize = originalFNameSize;
    unsigned int maxSize = 0;
    
    //get biggest file so we only need to call malloc once
    for(int i = 0; i < archive.numFiles; i++)
    {
        if(archive.entryInfo[i].size > maxSize)
            maxSize = archive.entryInfo[i].size;
    }

    buffer = malloc(maxSize);
    fname = malloc(fnamesize * 2);

    if((fname || buffer) == NULL)
    {
        return -1;
    }

    rewind(origin);
    chdir(outpath);
    fseek(origin, AFS_BODY_START,SEEK_SET);
    
    for(int i = 0; i < archive.numFiles; i++)
    {   
        fseek(origin, archive.entryInfo[i].offset, SEEK_CUR);
        fread(buffer, sizeof(char), archive.entryInfo[i].size, origin);

        sprintf(fname, "%d", i);

        f = fopen(fname, "w");

        if(f == NULL)
        {
            printf("%d\n", errno);
        }
        fwrite(buffer, sizeof(char), archive.entryInfo[i].size, f);
        fclose(f);
    }

    fclose(origin);
    free(buffer);
    free(originalFName);

    return 1;
}
int serializeArchive(const char *inputPath, const char *outputPath)
{
    struct afs_archive out;

    out = readAFSFile(inputPath);

    if(out.numFiles <= 0)
    {
        printf("Error reading the afs archive.\n %d is not a valid number of files", out.numFiles);
        return -1;
    }

    if(serializeOut(outputPath, out) != 1)
    {
        printf("Error, could not write the files in the archive to disc\n");
        return -2;
    }

    return 1;
}