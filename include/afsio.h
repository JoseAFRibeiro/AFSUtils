#ifndef AFSIO_H_
#define AFSIO_H_

int serializeArchive(const char *inputPath, const char *outputPath);
int isPath(const char *path);
struct afs_archive readAFSFile(const char *inputPath);


#endif 