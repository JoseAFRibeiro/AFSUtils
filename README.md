
# AFSUtils

A small tool/library for unpacking/packing AFS archives

## Licensing 

This entire repository is license under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)

## Compiling

This project comes with a Makefile configured for the GCC suite. It allows to compile the source down to an executable or a static library.

## AFSUtil

A command line tool to unpack/repack AFS archives

### Usage

AFSUtil requires two arguments, the first is the input AFS archive that will be unpacked, the second is the path where the files will be written to.

## libAFS

A C library that provides an easy way to unpack AFS archives

### Usage

Check the header ([libafs.h]() tba) to see the functions exposed by the library

## TODO

- Add packing functionality
- Improve makefiles
- Actual library build