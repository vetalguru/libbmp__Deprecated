CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

####################################
# VARIABLES
####################################
SET(LIB_ZLIB_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/zlib-1.2.8)
SET(LIB_PNG_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/libpng-1.6.19)
SET(LIBS_BUILD_PATH ${PROJECT_BINARY_DIR}/libs)

SET(CMAKE_LIBRARY_PATH ${LIBS_BUILD_PATH})


SET(INCLUDE_DIRS_LIST ${LIB_ZLIB_DIR}
                      ${LIB_PNG_DIR}
                      ${LIBS_BUILD_PATH})

SET(LIBRARY_OUTPUT_PATH ${LIBS_BUILD_PATH})

#######################################
# PROJECTS DIRECTORIES
#######################################
INCLUDE_DIRECTORIES(${INCLUDE_DIRS_LIST})

#######################################
# SUBDIRECTORIES
#######################################
ADD_SUBDIRECTORY(${LIB_ZLIB_DIR})
ADD_SUBDIRECTORY(${LIB_PNG_DIR})

