project('AFSUtils', 'c')

#add_project_arguments('-fstack-protector-all', language:'c')
#add_project_arguments('-Wstack-protector', language:'c')
#add_project_arguments('-Dlinux', language:'c')


add_project_arguments('-ggdb', language:'c')



sources = [
    './src/afs.c',
    './src/fileio.c',
    './src/libafs.c',
    './src/pathverify.c',
    './src/main.c',
]

include_dir = include_directories('include')


executable('afsutil', sources, include_directories:[include_dir])
