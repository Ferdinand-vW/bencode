# CMakeList.txt : CMake project for bencode, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("bencode")
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# Add source to this project's executable.
add_executable (bencode ${SOURCES})
target_compile_features(bencode PRIVATE cxx_std_17)

enable_testing()
add_subdirectory(test)