# Install script for directory: C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/src/core/Tools

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/BCI2000")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/CMakeFiles/core/Tools/BCI2000FileInfoQt/cmake_install.cmake")
  include("C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/CMakeFiles/core/Tools/BCI2000ViewerQt/cmake_install.cmake")
  include("C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/CMakeFiles/core/Tools/BCI2000ExportQt/cmake_install.cmake")
  include("C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/CMakeFiles/core/Tools/BCI2000LauncherQt/cmake_install.cmake")
  include("C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/CMakeFiles/core/Tools/BCI2000MediaPlayer/cmake_install.cmake")
  include("C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/CMakeFiles/core/Tools/P300Classifier/cmake_install.cmake")
  include("C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/CMakeFiles/core/Tools/BCI2000Certification/cmake_install.cmake")
  include("C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/CMakeFiles/core/Tools/BCI2000Analysis/cmake_install.cmake")
  include("C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/CMakeFiles/core/Tools/BCI2000Watchdog/cmake_install.cmake")
  include("C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/CMakeFiles/core/Tools/cmdline/cmake_install.cmake")
  include("C:/Users/kotlab/Documents/GitHub/BCI-Group/BCI2000/build/CMakeFiles/core/Tools/mex/cmake_install.cmake")

endif()

