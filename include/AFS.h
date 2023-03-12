#ifndef AFS_H_
#define AFS_H_

#define AFS_ARCHIVE_STRUCT_SIZE 0x08
#define AFS_ARCHIVE_STRUCT_OFFSET 0x08
#define AFS_SIZE_DWORD 0x04

struct afs_entry{
    unsigned long size;
    unsigned long offset;
};

struct afs_archive{

    unsigned int numFiles;
    struct afs_entry *entryInfo; 
};

#endif 