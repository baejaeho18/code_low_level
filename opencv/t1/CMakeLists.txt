cmake_minimum_required (VERSION 3.22)

project (t1)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_COMPILER "g++")

set (SOURCES main.cpp)

find_package(OpenCV REQUIRED)

include_directories (
  /usr/local/include 
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable (t1 ${SOURCES})

target_link_libraries (t1 
  ${OpenCV_LIBS}
)
