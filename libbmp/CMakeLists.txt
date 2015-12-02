CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#######################################
# VARIABLES
#######################################
SET(PROJECT_NAME bmp)

SET(SOURCES_LIST ${CMAKE_CURRENT_SOURCE_DIR}/libbmp.cpp)


PROJECT(${PROJECT_NAME})

ADD_LIBRARY(${PROJECT_NAME} STATIC ${SOURCES_LIST})

