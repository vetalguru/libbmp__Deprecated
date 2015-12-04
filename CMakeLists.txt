CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

####################################
# VARIABLES
####################################
SET(PROJECT_NAME BMPSample)
SET(SAMPLE_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sample)
SET(TESTS_PROJECT_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/tests)
SET(GTEST_SUBDIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/gtest-1.7.0)
SET(LIB_BMP_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/libbmp)
SET(LIB_ZLIB_DIR       ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/zlib-1.2.8)
SET(LIB_PNG_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libpng-1.6.19)

SET(INCLUDE_DIRS_LIST ${gtest_SOURCE_DIR}/include
                      ${gtest_SOURCE_DIR}
                      ${SAMPLE_PROJECT_DIR}
                      ${TESTS_PROJECT_DIR}
                      ${LIB_BMP_DIR}
                      ${LIB_ZLIB_DIR}
                      ${LIB_PNG_DIR})

#######################################
# PROJECT NAME
#######################################
PROJECT(${PROJECT_NAME})

#######################################
# PROJECTS DIRECTORIES
#######################################
INCLUDE_DIRECTORIES(${INCLUDE_DIRS_LIST})

#######################################
# SUBDIRECTORIES
#######################################
ADD_SUBDIRECTORY(${GTEST_SUBDIRECTORY})
ADD_SUBDIRECTORY(${LIB_BMP_DIR})
ADD_SUBDIRECTORY(${LIB_ZLIB_DIR})
ADD_SUBDIRECTORY(${LIB_PNG_DIR})
ADD_SUBDIRECTORY(${SAMPLE_PROJECT_DIR})
ADD_SUBDIRECTORY(${TESTS_PROJECT_DIR})

