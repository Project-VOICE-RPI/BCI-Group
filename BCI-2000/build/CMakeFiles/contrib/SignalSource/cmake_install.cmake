# Install script for directory: /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/src/contrib/SignalSource

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/lib/qt6/bin")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/RDAClient/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/Neuroscan/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/FieldTripBufferSource/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/FilePlayback/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/Blackrock/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/Ripple/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/DSISerial/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/LSLSource/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/OpenBCISource/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/OpenBCI_Module/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/actiCHampPlus/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/NeuroSpark/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/NeuSenW/cmake_install.cmake")
  include("/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/CMakeFiles/contrib/SignalSource/LabJackSource/cmake_install.cmake")

endif()

