cmake_minimum_required (VERSION 3.8)

file(GLOB SOURCES "*.cpp")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.74.0)

# Add source to this project's executable.
add_executable (bencode_run ${SOURCES})
target_include_directories(bencode_run PUBLIC 
    $<BUILD_INTERFACE:${BUILD_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(bencode_run PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            )

add_library(bencode STATIC ${SOURCES})
target_include_directories(bencode PUBLIC
    $<BUILD_INTERFACE:${BUILD_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
    
set_target_properties(bencode PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            )


install(TARGETS bencode_run DESTINATION ${CMAKE_INSTALL_BINDIR}/${LIBNAME})
install(TARGETS bencode EXPORT ${LIBNAME} DESTINATION ${CMAKE_INSTALL_LIBDIR}/${LIBNAME})
install(EXPORT bencode FILE ${LIBNAME}Configjk.cmake NAMESPACE ${LIBNAME}:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBNAME})
export(EXPORT bencode FILE ${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}.cmake)
export(PACKAGE bencode)
