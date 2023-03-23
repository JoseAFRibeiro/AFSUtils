#include "afsio.h"
#include "AFS.h"

struct afs_archive unpackArchive(const char *AFSarchivePath)
{
    struct afs_archive archive = {0};

    if(!isPath(AFSarchivePath))
        return archive;
    
    archive = readAFSFile(AFSarchivePath);

    return archive;
}
int packFiles()
{
    return 0;
}