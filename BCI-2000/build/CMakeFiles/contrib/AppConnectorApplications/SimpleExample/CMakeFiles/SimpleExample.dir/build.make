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
include CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/flags.make

CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/SimpleExample.cpp.o: CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/flags.make
CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/SimpleExample.cpp.o: /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/contrib/AppConnectorApplications/SimpleExample/SimpleExample.cpp
CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/SimpleExample.cpp.o: CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/SimpleExample.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/SimpleExample.cpp.o -MF CMakeFiles/SimpleExample.dir/SimpleExample.cpp.o.d -o CMakeFiles/SimpleExample.dir/SimpleExample.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/contrib/AppConnectorApplications/SimpleExample/SimpleExample.cpp

CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/SimpleExample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SimpleExample.dir/SimpleExample.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/contrib/AppConnectorApplications/SimpleExample/SimpleExample.cpp > CMakeFiles/SimpleExample.dir/SimpleExample.cpp.i

CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/SimpleExample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SimpleExample.dir/SimpleExample.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/contrib/AppConnectorApplications/SimpleExample/SimpleExample.cpp -o CMakeFiles/SimpleExample.dir/SimpleExample.cpp.s

CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.o: CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/flags.make
CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.o: /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp
CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.o: CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.o"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.o -MF CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.o.d -o CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.o -c /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp

CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.i"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp > CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.i

CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.s"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp -o CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.s

# Object files for target SimpleExample
SimpleExample_OBJECTS = \
"CMakeFiles/SimpleExample.dir/SimpleExample.cpp.o" \
"CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.o"

# External object files for target SimpleExample
SimpleExample_EXTERNAL_OBJECTS =

CMakeFiles/contrib/AppConnectorApplications/SimpleExample/SimpleExample: CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/SimpleExample.cpp.o
CMakeFiles/contrib/AppConnectorApplications/SimpleExample/SimpleExample: CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/shared/utils/Lib/SockStream.cpp.o
CMakeFiles/contrib/AppConnectorApplications/SimpleExample/SimpleExample: CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/build.make
CMakeFiles/contrib/AppConnectorApplications/SimpleExample/SimpleExample: CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable SimpleExample"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SimpleExample.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold "Copy to destination"
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample && /usr/bin/cmake -E make_directory /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/contrib/AppConnectorApplications/SimpleExample
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample && /usr/bin/cmake -E copy /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample/SimpleExample /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/contrib/AppConnectorApplications/SimpleExample || /usr/bin/cmake -E remove /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample/SimpleExample && /usr/bin/cmake -E touch_nocreate .notexist

# Rule to build all files generated by this target.
CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/build: CMakeFiles/contrib/AppConnectorApplications/SimpleExample/SimpleExample
.PHONY : CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/build

CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/clean:
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample && $(CMAKE_COMMAND) -P CMakeFiles/SimpleExample.dir/cmake_clean.cmake
.PHONY : CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/clean

CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/depend:
	cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/contrib/AppConnectorApplications/SimpleExample /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/contrib/AppConnectorApplications/SimpleExample/CMakeFiles/SimpleExample.dir/depend
