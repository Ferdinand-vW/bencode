# CMakeList.txt : CMake project for bencode, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("bencode")

# Add source to this project's executable.
add_executable (bencode "bencode.cpp" "bencode.h")

# TODO: Add tests and install targets if needed.
