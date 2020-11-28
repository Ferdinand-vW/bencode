cmake_minimum_required (VERSION 3.8)

find_package(Boost 1.74.0 REQUIRED COMPONENTS unit_test_framework)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

add_definitions( -DBOOST_ALL_NO_LIB )
add_definitions( -DBOOST_ALL_DYN_LINK )

include_directories(include)

add_executable(Empty empty.cpp)
add_test(NAME bstring_empty COMMAND Empty)
target_link_libraries(Empty bencode_lib ${Boost_LIBRARIES})

add_executable(Identity identity.cpp)
add_test(NAME bencode_identity COMMAND Identity)
target_link_libraries(Identity bencode_lib ${Boost_LIBRARIES})

add_executable(Error error.cpp)
add_test(NAME bencode_error COMMAND Error)
target_link_libraries(Error bencode_lib ${Boost_LIBRARIES})