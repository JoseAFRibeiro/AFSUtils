#include "AFS.h"
#include "afsio.h"

struct afs_archive libafs_readAFSFile(const char *filepath)
{
    struct afs_archive archive = {0};

    if(!isPath(filepath))
    {
        return archive;
    }

    archive = readAFSFile(filepath);

    return archive;
}