# CMakeList.txt : CMake project for bencode, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("bencode")

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_subdirectory(src)
enable_testing()
add_subdirectory(test)