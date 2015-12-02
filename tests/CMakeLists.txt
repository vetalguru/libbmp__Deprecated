CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#######################################
# VARIABLES
#######################################
SET(PROJECT_NAME tests)
SET(LIB_BMP_PATH ${PROJECT_SOURCE_DIR}/libbmp)
SET(GTEST_SUBDIRECTORY ${CMAKE_SOURCE_DIR}/thirdparty/gtest-1.7.0)

SET(SOURCES_LIST ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

SET(INCLUDE_DIRS_LIST ${gtest_SOURCE_DIR}/include
                      ${gtest_SOURCE_DIR}
                      ${LIB_BMP_PATH})

#######################################
# PROJECT NAME
#######################################
PROJECT(${PROJECT_NAME})

#######################################
# PROJECTS SUBDIRECTORIES
#######################################
INCLUDE_DIRECTORIES(${INCLUDE_DIRS_LIST})

enable_testing()

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES_LIST})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} gtest
                                      gtest_main
                                      bmp)

