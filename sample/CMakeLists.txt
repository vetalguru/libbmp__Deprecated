CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#######################################
# VARIABLES
#######################################
SET(PROJECT_NAME sample)
SET(LIB_BMP_PATH ${PROJECT_SOURCE_DIR}/libbmp)

SET(HEADERS_LIST ${LIB_BMP_PATH}/libbmp.h)

SET(SOURCES_LIST ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

#######################################
# PROJECT NAME
#######################################
PROJECT(${PROJECT_NAME})

#######################################
# PROJECTS SUBDIRECTORIES
#######################################
INCLUDE_DIRECTORIES(LIB_BMP_PATH)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES_LIST} ${HEADERS_LIST})

