###########################################################################
## $Id: CMakeLists.txt 8120 2024-05-08 16:37:53Z mellinger $
## Authors: juergen.mellinger@uni-tuebingen.de
## Description: Build information for BCI2000RemoteLib

# Set the executable name
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  SET( NAME BCI2000RemoteLib32 )
else()
  SET( NAME BCI2000RemoteLib64 )
endif()

SET( SRC_PROJECT
  BCI2000RemoteLib.cpp
  BCI2000Connection.cpp
  BCI2000Remote.cpp
  ${PROJECT_SRC_DIR}/shared/utils/Lib/SockStream.cpp
  ${PROJECT_SRC_DIR}/shared/utils/Lib/SelfPipe.cpp
)

ADD_DEFINITIONS(
  -DLIBREMOTE_LIBRARY=1
)

SET( LIBS "" )
IF( WIN32 )
  SET( LIBS
    ${LIBS}
    ws2_32
  )
ELSE()
  SET( LIBS
    ${LIBS}
    pthread
  )
ENDIF()

set_crt_link_type( STATIC )
BCI2000_ADD_TARGET( DLL ${NAME} ${SRC_PROJECT} )
SET_OUTPUT_DIRECTORY( "${PROJECT_BUILD_ROOT}/prog" ${NAME} )
