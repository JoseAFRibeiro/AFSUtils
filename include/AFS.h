#ifndef AFS_H_
#define AFS_H_

#define AFS_ARCHIVE_STRUCT_SIZE 0x08
#define AFS_ARCHIVE_STRUCT_OFFSET 0x08
#define AFS_SIZE_DWORD 4 * sizeof(char)
#define AFS_BODY_START 0x800000

struct afs_entry{
    unsigned long offset;
    unsigned long size;
};

struct afs_archive{
    unsigned int numFiles;
    struct afs_entry *entryInfo; 
};

struct afs_archive unpackArchive(const char *AFSarchivePath);
int packFiles();


#endif 