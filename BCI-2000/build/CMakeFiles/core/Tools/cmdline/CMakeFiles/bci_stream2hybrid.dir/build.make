# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build

# Include any dependencies generated for this target.
include CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/flags.make

CMakeFiles/core/Tools/cmdline/bci_stream2hybrid_/puzzlepiece256.png.res.cpp: CMakeFiles/buildutils/create_resource
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid_/puzzlepiece256.png.res.cpp: CMakeFiles/icons/puzzlepiece256.png
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating bci_stream2hybrid_/puzzlepiece256.png.res.cpp"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/buildutils/create_resource AppIcon256 /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/icons/puzzlepiece256.png > /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline/bci_stream2hybrid_/puzzlepiece256.png.res.cpp

CMakeFiles/icons/puzzlepiece256.png: CMakeFiles/buildutils/transform_png
CMakeFiles/icons/puzzlepiece256.png: CMakeFiles/buildutils/combine_png
CMakeFiles/icons/puzzlepiece256.png: cmake/MakeIcon.cmake
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating ../../../icons/puzzlepiece256.png"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/icons && /usr/bin/cmake -DBUILDUTILS_DIR=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/buildutils -DPROJECT_ICON_TEMPLATE=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/gui/images/brain-outline -DSTYLE= -DICON=puzzlepiece -DOUTPUT=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/icons/puzzlepiece256.png -P /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/cmake/MakeIcon.cmake

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.o: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/flags.make
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.o: /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/Tools/cmdline/bci_tool.cpp
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.o: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.o -MF CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.o.d -o CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/Tools/cmdline/bci_tool.cpp

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/Tools/cmdline/bci_tool.cpp > CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.i

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/Tools/cmdline/bci_tool.cpp -o CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.s

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.o: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/flags.make
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.o: /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/Tools/cmdline/bci_stream2hybrid.cpp
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.o: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.o -MF CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.o.d -o CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/Tools/cmdline/bci_stream2hybrid.cpp

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/Tools/cmdline/bci_stream2hybrid.cpp > CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.i

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/Tools/cmdline/bci_stream2hybrid.cpp -o CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.s

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.o: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/flags.make
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.o: /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.o: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.o -MF CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.o.d -o CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp > CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.i

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp -o CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.s

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.o: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/flags.make
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.o: CMakeFiles/core/Tools/cmdline/bci_stream2hybrid_/puzzlepiece256.png.res.cpp
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.o: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.o -MF CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.o.d -o CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline/bci_stream2hybrid_/puzzlepiece256.png.res.cpp

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline/bci_stream2hybrid_/puzzlepiece256.png.res.cpp > CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.i

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline/bci_stream2hybrid_/puzzlepiece256.png.res.cpp -o CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.s

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.o: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/flags.make
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.o: CMakeFiles/version/Version.cpp
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.o: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.o -MF CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.o.d -o CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/version/Version.cpp

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/version/Version.cpp > CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.i

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/version/Version.cpp -o CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.s

# Object files for target bci_stream2hybrid
bci_stream2hybrid_OBJECTS = \
"CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.o" \
"CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.o" \
"CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.o" \
"CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.o" \
"CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.o"

# External object files for target bci_stream2hybrid
bci_stream2hybrid_EXTERNAL_OBJECTS =

CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_tool.cpp.o
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid.cpp.o
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_tool.cpp.o
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/bci_stream2hybrid_/puzzlepiece256.png.res.cpp.o
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/__/__/__/version/Version.cpp.o
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/build.make
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/CoreLib/StaticCrt/libBCI2000FrameworkCore_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/LibTiny/StaticCrt/libLibTiny_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/CoreLib/StaticCrt/libBCI2000FrameworkCore_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/LibTiny/StaticCrt/libLibTiny_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/CoreLib/StaticCrt/libBCI2000FrameworkCore_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/LibTiny/StaticCrt/libLibTiny_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/CoreLib/StaticCrt/libBCI2000FrameworkCore_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/LibTiny/StaticCrt/libLibTiny_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/CoreLib/StaticCrt/libBCI2000FrameworkCore_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/LibTiny/StaticCrt/libLibTiny_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/CoreLib/StaticCrt/libBCI2000FrameworkCore_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/LibTiny/StaticCrt/libLibTiny_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/CoreLib/StaticCrt/libBCI2000FrameworkCore_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/LibTiny/StaticCrt/libLibTiny_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/CoreLib/StaticCrt/libBCI2000FrameworkCore_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/frameworks/LibTiny/StaticCrt/libLibTiny_StaticCrt.a
CMakeFiles/core/Tools/cmdline/bci_stream2hybrid: CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable bci_stream2hybrid"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bci_stream2hybrid.dir/link.txt --verbose=$(VERBOSE)
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/cmake -E touch /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/version/VersionCheck
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold "Copy to destination"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/cmake -E make_directory /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000//tools/cmdline
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && /usr/bin/cmake -E copy /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline/bci_stream2hybrid /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000//tools/cmdline || /usr/bin/cmake -E remove /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline/bci_stream2hybrid && /usr/bin/cmake -E touch_nocreate .notexist

# Rule to build all files generated by this target.
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/build: CMakeFiles/core/Tools/cmdline/bci_stream2hybrid
.PHONY : CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/build

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/clean:
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline && $(CMAKE_COMMAND) -P CMakeFiles/bci_stream2hybrid.dir/cmake_clean.cmake
.PHONY : CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/clean

CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/depend: CMakeFiles/core/Tools/cmdline/bci_stream2hybrid_/puzzlepiece256.png.res.cpp
CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/depend: CMakeFiles/icons/puzzlepiece256.png
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/Tools/cmdline /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/core/Tools/cmdline/CMakeFiles/bci_stream2hybrid.dir/depend

