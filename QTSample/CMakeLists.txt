cmake_minimum_required (VERSION 2.8.11)

# VARIABLES
set(PROJECT_NAME QtSample)


set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers)
set(UI_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/ui)
set(LIB_BMP_DIR ${PROJECT_BINARY_DIR}/libbmp)

set(SOURCES_LIST ${SOURCES_DIR}/main.cpp
                 ${SOURCES_DIR}/mainwindow.cpp
                 ${SOURCES_DIR}/bitmapview.cpp)

set(HEADERS_LIST  ${HEADERS_DIR}/mainwindow.h
                  ${HEADERS_DIR}/bitmapview.h)

set(UI_FILES_LIST ${UI_DIR}/mainwindow.ui)

project(${PROJECT_NAME})

include_directories(${SOURCES_DIR})
include_directories(${HEADERS_DIR})
include_directories(${UI_DIR})
include_directories(${LIB_BMP_DIR})

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_ui(UI_FILES_H ${UI_FILES_LIST})

add_executable(${PROJECT_NAME} ${SOURCES_LIST} ${HEADERS_LIST} ${UI_FILES_H})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} bmp)
