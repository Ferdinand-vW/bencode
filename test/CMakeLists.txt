find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(Test test.cpp)
target_link_libraries(Test ${Boost_UNIT_TEST_FRAMEWORK})

add_test(NAME test COMMAND Test)