# CMakeList.txt : CMake project for bencode, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project (bencode VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "default install path" FORCE)
set(PROJ_VER_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}")
set(BUILD_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin/${PROJ_VER_NAME}")
set(INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include/${PROJ_VER_NAME}")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib/${PROJ_VER_NAME}")

add_custom_target(build_tests)
add_custom_target(run_tests COMMAND ${CMAKE_CTEST_COMMAND})
add_dependencies(run_tests build_tests)

add_subdirectory(src)
add_subdirectory(include)
enable_testing()
add_subdirectory(test EXCLUDE_FROM_ALL)
