# CMakeList.txt : CMake project for bencode, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("bencode")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source to this project's executable.
add_executable (bencode "bencode.cpp"  "btypes.h" "blist.h" "bencode.h" "bdict.h"  "decode.cpp" "bstring.h"  "decode.h" "bint.h" "bdict.cpp" "blist.cpp" "utils.h")
target_compile_features(bencode PRIVATE cxx_std_17)