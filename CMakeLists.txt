# CMakeList.txt : CMake project for bencode, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("bencode")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "default install path")
set(INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")

include_directories(include)
add_subdirectory(src)
add_subdirectory(include)
enable_testing()
add_subdirectory(test)