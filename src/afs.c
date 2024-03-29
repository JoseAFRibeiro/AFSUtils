#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "afsio.h"
#include "AFS.h"

static FILE *origin;

static inline int readHeader(FILE *f)
{
    char header[AFS_SIZE_DWORD];

    if(f == NULL)
        return 1;
    
    fread(header, sizeof(char), AFS_SIZE_DWORD, f);
    fseek(f, AFS_SIZE_DWORD, SEEK_SET);
     
    if(strcmp(header, "AFS\0"))
    {
        return -1;
    }
    
    return 0;
}
static inline void indexFiles(FILE *f, struct afs_archive *archive)
{
    fread(&archive->numFiles, sizeof(int), 1, f);
    archive->entryInfo = malloc(sizeof(struct afs_entry) * archive->numFiles);
    
   for(int i = 0; i< archive->numFiles; i++)
    {
        fread(&archive->entryInfo[i].offset, AFS_SIZE_DWORD, 1, f);
        fread(&archive->entryInfo[i].size, AFS_SIZE_DWORD, 1, f);

    }
    return;
}

struct afs_archive readAFSFile(const char *inputPath)
{
    long fileSize;
    int result;
    struct afs_archive archive;

    FILE *f = readFile(inputPath, &fileSize);
    
    result = readHeader(f);

    if(result != 0)
    {
        struct afs_archive err = {0};
        return err;
    }

    indexFiles(f, &archive);
    origin = f;
    return archive;
}

static inline int serializeOut(const char *outpath, struct afs_archive archive)
{
    FILE *f;
    char *buffer;
    char outFileName[12];
    unsigned int maxSize = 0;
    
    //get biggest file so we only need to call malloc once
    for(int i = 0; i < archive.numFiles; i++)
    {
        if(archive.entryInfo[i].size > maxSize)
            maxSize = archive.entryInfo[i].size;
    }

    buffer = malloc(maxSize);

    if(buffer == NULL)
    {
        return -1;
    }

    rewind(origin);
    chdir(outpath);
    fseek(origin, AFS_BODY_START,SEEK_SET);
    
    for(int i = 0; i < archive.numFiles; i++)
    {   
        fseek(origin, archive.entryInfo[i].offset, SEEK_SET);
        fread(buffer, sizeof(char), archive.entryInfo[i].size, origin);
        sprintf(outFileName, "%d", i);

        f = fopen(outFileName, "w");

        if(f == NULL)
        {
            break;
        }

        fwrite(buffer, sizeof(char), archive.entryInfo[i].size, f);
        fclose(f);
    }

    fclose(origin);
    free(buffer);

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
    
    free(out.entryInfo);

    return 1;
}

//AFS file packing
#define AFS_MAGIC_WORD "AFS\0"

static inline struct afs_archival_entry *indexFilesArchival(unsigned int fcount, const char ** paths)
{
    struct afs_archival_entry *archives = malloc(sizeof(struct afs_archival_entry) * fcount);

    if(archives == NULL)
        return NULL;

    for(int i = 0; i < fcount; i++ )
    {
       archives[i].f = fopen(paths[i], "rb");
       archives[i].size = getFileSize(archives->f);
    }   

    return archives;
}

static inline void calculateOffsets(unsigned int fcount, struct afs_archival_entry *entries)
{
    unsigned int currentOffset = AFS_BODY_START;
    unsigned int cursor = AFS_BODY_START;

    entries[0].offset = AFS_BODY_START;
    cursor += entries[0].size;

    int multiple;

    for(int i = 1; i < fcount; i++)
    {   
        multiple = cursor / 0x0100;
        cursor = (multiple + 1) * 256;

        entries[i].offset = cursor;
        cursor += entries[i].size;  
    }
}

static inline unsigned int calculateArchiveSize(unsigned int size, unsigned int offset)
{
    return size + offset;
}

static inline void writeToArchive(struct afs_archival_entry *archives, unsigned int entryCount, char *buffer )
{

}

int archiveFiles(const char* outPath, const char **entries, unsigned int entryCount)
{
    FILE *f = fopen(outPath, "w");

    if(f == NULL)
        return -1;

    struct afs_archival_entry *archives = indexFilesArchival(entryCount, entries);

    if(archives == NULL)
        return -2;

    calculateOffsets(entryCount, archives);
    int archiveSize = calculateArchiveSize(archives[entryCount - 1].size, archives[entryCount - 1].offset);

    char * archive = malloc(archiveSize);

    if(archive == NULL)
        return -2;

    return 0;
}