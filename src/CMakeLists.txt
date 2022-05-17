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

include(GNUInstallDirs)

# Add target to export set
install(TARGETS ${LIBNAME}
        EXPORT ${LIBNAME}Targets
        LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/${LIBNAME})

# Install export set in install destination
install(EXPORT ${LIBNAME}Targets
        NAMESPACE ${LIBNAME}::
        FILE ${LIBNAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBNAME})

include(CMakePackageConfigHelpers)

configure_package_config_file(
        "Config.cmake.in"
        "${LIBNAME}Config.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBNAME}
        PATH_VARS CMAKE_INSTALL_LIBDIR
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}ConfigVersion.cmake
        VERSION 1.0.0
        COMPATIBILITY SameMajorVersion
)

install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}Config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}ConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${LIBNAME}"
)

