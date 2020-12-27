cmake_minimum_required (VERSION 3.8)

find_package(Boost 1.74.0 REQUIRED COMPONENTS unit_test_framework)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

add_definitions( -DBOOST_ALL_NO_LIB )
add_definitions( -DBOOST_ALL_DYN_LINK )

include_directories(include)

add_executable(empty empty.cpp)
add_test(NAME bencode_empty COMMAND empty)
target_link_libraries(empty bencode_lib ${Boost_LIBRARIES})

add_executable(identity identity.cpp)
add_test(NAME bencode_identity COMMAND identity)
target_link_libraries(identity bencode_lib ${Boost_LIBRARIES})

add_executable(error error.cpp)
add_test(NAME bencode_error COMMAND error)
target_link_libraries(error bencode_lib ${Boost_LIBRARIES})

add_dependencies(build_tests empty identity error)