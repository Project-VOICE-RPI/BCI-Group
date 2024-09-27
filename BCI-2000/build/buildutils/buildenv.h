#ifndef BUILDENV_H
#define BUILDENV_H

#define CMAKE_C_COMPILER "/usr/bin/cc"
#define CMAKE_CXX_COMPILER "/usr/bin/c++"
#define CMAKE_C_FLAGS " -DNDEBUG=1 -include "/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000//src/shared/config/gccprefix.h" -openmp -fPIC -fvisibility=hidden -D_FILE_OFFSET_BITS=64 -Wstrict-aliasing -Wno-endif-labels -Wno-multichar -Wno-enum-compare -Wno-narrowing"
#define CMAKE_CXX_FLAGS " -DNDEBUG=1 -include "/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000//src/shared/config/gccprefix.h" -openmp -fPIC -fvisibility=hidden -D_FILE_OFFSET_BITS=64 -Wstrict-aliasing -Wno-endif-labels -Wno-multichar -Wno-enum-compare -Wno-narrowing -std=c++17"
#define CMAKE_C_COMPILER_ID "GNU"
#define CMAKE_CXX_COMPILER_ID "GNU"
#define CMAKE_SOURCE_DIR "/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build"
#define CMAKE_BINARY_DIR "/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build"

#endif // BUILDENV_H
