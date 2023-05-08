cmake_minimum_required (VERSION 3.8)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(
    empty
    empty.cpp
)

target_link_libraries(empty gtest_main bencode)

add_executable(
    identity
    identity.cpp
)

target_link_libraries(identity gtest_main bencode)

add_executable(
    bsort
    bsort.cpp
)

target_link_libraries(bsort gtest_main bencode)

add_executable(
    error
    error.cpp
)

target_link_libraries(error gtest_main bencode)


include(GoogleTest)
gtest_discover_tests(empty)
gtest_discover_tests(identity)
gtest_discover_tests(bsort)
gtest_discover_tests(error)