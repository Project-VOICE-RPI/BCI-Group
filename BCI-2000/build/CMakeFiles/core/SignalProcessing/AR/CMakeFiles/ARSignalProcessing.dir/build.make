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
include CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/flags.make

CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing_/cogwheel-screen256.png.res.cpp: CMakeFiles/buildutils/create_resource
CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing_/cogwheel-screen256.png.res.cpp: CMakeFiles/icons/cogwheel-screen256.png
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ARSignalProcessing_/cogwheel-screen256.png.res.cpp"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/buildutils/create_resource AppIcon256 /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/icons/cogwheel-screen256.png > /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing_/cogwheel-screen256.png.res.cpp

CMakeFiles/icons/cogwheel-screen256.png: CMakeFiles/buildutils/transform_png
CMakeFiles/icons/cogwheel-screen256.png: CMakeFiles/buildutils/combine_png
CMakeFiles/icons/cogwheel-screen256.png: cmake/MakeIcon.cmake
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating ../../../icons/cogwheel-screen256.png"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/icons && /usr/bin/cmake -DBUILDUTILS_DIR=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/buildutils -DPROJECT_ICON_TEMPLATE=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/gui/images/brain-outline -DSTYLE= -DICON=cogwheel-screen -DOUTPUT=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/icons/cogwheel-screen256.png -P /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/cmake/MakeIcon.cmake

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/flags.make
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.o: /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/SignalProcessing/AR/PipeDefinition.cpp
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.o -MF CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.o.d -o CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/SignalProcessing/AR/PipeDefinition.cpp

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/SignalProcessing/AR/PipeDefinition.cpp > CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.i

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/SignalProcessing/AR/PipeDefinition.cpp -o CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.s

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/flags.make
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.o: /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.o -MF CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.o.d -o CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp > CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.i

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp -o CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.s

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/flags.make
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.o: /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.o -MF CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.o.d -o CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp > CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.i

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp -o CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.s

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/flags.make
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.o: /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.o -MF CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.o.d -o CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp > CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.i

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp -o CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.s

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/flags.make
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.o: CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing_/cogwheel-screen256.png.res.cpp
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.o -MF CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.o.d -o CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing_/cogwheel-screen256.png.res.cpp

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing_/cogwheel-screen256.png.res.cpp > CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.i

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing_/cogwheel-screen256.png.res.cpp -o CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.s

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/flags.make
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.o: CMakeFiles/version/Version.cpp
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.o: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.o -MF CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.o.d -o CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/version/Version.cpp

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/version/Version.cpp > CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.i

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/version/Version.cpp -o CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.s

# Object files for target ARSignalProcessing
ARSignalProcessing_OBJECTS = \
"CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.o" \
"CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.o" \
"CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.o" \
"CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.o" \
"CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.o" \
"CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.o"

# External object files for target ARSignalProcessing
ARSignalProcessing_EXTERNAL_OBJECTS =

CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/PipeDefinition.cpp.o
CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreMain.cpp.o
CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/modules/CoreModule.cpp.o
CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/bcistream/BCIStream_module.cpp.o
CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/ARSignalProcessing_/cogwheel-screen256.png.res.cpp.o
CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/__/__/__/version/Version.cpp.o
CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/build.make
CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing: CMakeFiles/frameworks/SigProcModuleLib/libBCI2000FrameworkSigProcModule.a
CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing: CMakeFiles/frameworks/CoreLib/DynamicCrt/libBCI2000FrameworkCore_DynamicCrt.a
CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing: CMakeFiles/frameworks/LibTiny/DynamicCrt/libLibTiny_DynamicCrt.a
CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing: CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable ARSignalProcessing"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ARSignalProcessing.dir/link.txt --verbose=$(VERBOSE)
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/cmake -E touch /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/version/VersionCheck
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold "Copy to destination"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/cmake -E make_directory /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000//prog
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && /usr/bin/cmake -E copy /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000//prog || /usr/bin/cmake -E remove /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing && /usr/bin/cmake -E touch_nocreate .notexist

# Rule to build all files generated by this target.
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/build: CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing
.PHONY : CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/build

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/clean:
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR && $(CMAKE_COMMAND) -P CMakeFiles/ARSignalProcessing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/clean

CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/depend: CMakeFiles/core/SignalProcessing/AR/ARSignalProcessing_/cogwheel-screen256.png.res.cpp
CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/depend: CMakeFiles/icons/cogwheel-screen256.png
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/core/SignalProcessing/AR /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/core/SignalProcessing/AR/CMakeFiles/ARSignalProcessing.dir/depend

