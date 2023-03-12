#include "afsio.h"
#ifdef linux
#include <sanitizer/asan_interface.h>
#endif
int main(int argc, char const *argv[])
{

    const char *input, *output;
    #ifdef linux
    __sanitizer_set_report_path("./stackdebug.txt");
    #endif
    if(argc != 3)
    {
        printf("Error, too few or too many arguments.\nTo use this program provide an input file, an output location and operation mode");
        return -1;
    }

    input = argv[1];
    output = argv[2];

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

    readAFSFile(input, output);
    
    return 0;
}
