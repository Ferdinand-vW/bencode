cmake_minimum_required (VERSION 3.8)

file(GLOB SOURCES "*.cpp")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.74.0)

# Add source to this project's executable.
add_executable (bencode_run ${SOURCES})

set_target_properties(bencode_run PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            )

add_library(bencode_lib STATIC ${SOURCES})

set_target_properties(bencode_lib PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            )


install(TARGETS bencode_lib DESTINATION ${INSTALL_LIB_DIR})
