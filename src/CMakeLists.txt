cmake_minimum_required (VERSION 3.8)

file(GLOB SOURCES "*.cpp")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.80.0)

# Add source to this project's executable.
add_executable (bencode_run ${SOURCES})
target_link_libraries(bencode_run ${BOOST_LIBRARIES})
target_include_directories(bencode_run PUBLIC 
    $<BUILD_INTERFACE:${BUILD_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

add_library(bencode STATIC ${SOURCES})
target_link_libraries(bencode ${BOOST_LIBRARIES})
target_include_directories(bencode PUBLIC
    $<BUILD_INTERFACE:${BUILD_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>)
    
include(GNUInstallDirs)

# Add target to export set
install(TARGETS bencode
        EXPORT bencodeTargets
        ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Install export set in install destination
install(EXPORT bencodeTargets
        FILE bencode.cmake
        DESTINATION lib/cmake/bencode)

include(CMakePackageConfigHelpers)

configure_package_config_file(
        "Config.cmake.in"
        "bencodeConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bencode
        PATH_VARS CMAKE_INSTALL_LIBDIR
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/bencodeConfigVersion.cmake
        VERSION 1.0.0
        COMPATIBILITY AnyNewerVersion
)

install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/bencodeConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/bencodeConfigVersion.cmake
        DESTINATION lib/cmake/bencode
)

export(EXPORT bencodeTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/bencode.cmake"
)

