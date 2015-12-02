CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#######################################
# VARIABLES
#######################################
SET(PROJECT_NAME sample)
SET(LIB_BMP_PATH ${PROJECT_SOURCE_DIR}/libbmp)

SET(SOURCES_LIST ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

SET(INCLUDE_DIRS_LIST ${LIB_BMP_PATH})

#######################################
# PROJECT NAME
#######################################
PROJECT(${PROJECT_NAME})

#######################################
# PROJECTS SUBDIRECTORIES
#######################################
INCLUDE_DIRECTORIES(${INCLUDE_DIRS_LIST})

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES_LIST})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} bmp)

