#include "afsio.h"
#include "AFS.h"
#ifdef linux
#include <sanitizer/asan_interface.h>
#endif
int main(int argc, char const *argv[])
{

    const char *input, *output, *mode;
    #ifdef linux
    __sanitizer_set_report_path("./stackdebug.txt");
    #endif
    if(argc < 3)
    {
        printf("Error, too few or too many arguments.\nTo use this program provide an input file, an output location and operation mode");
        return -1;
    }

    input = argv[1];
    output = argv[2];
    mode = argv[3];

    if(!isPath(input))
    {
        printf("Input path does not exist!\n");
        return -1;
    }     

    if(!isPath(output))
    {
        printf("Output path does not exist!\n");
        return -1;
    }
    
    struct afs_archive archive = libafs_readAFSFile(input);
    return 0; 
    
}
