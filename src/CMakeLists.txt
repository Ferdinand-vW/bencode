cmake_minimum_required (VERSION 3.8)

file(GLOB SOURCES "*.cpp")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.74.0)

# Add source to this project's executable.
add_executable (bencode_run ${SOURCES})
add_library(bencode_lib STATIC ${SOURCES})

install(TARGETS bencode_lib DESTINATION lib)
install(FILES ../include/bdata.h ../include/bdict.h ../include/bencode.h ../include/bint.h ../include/blist.h ../include/bstring.h ../include/btypes.h ../include/decode.h ../include/encode.h ../include/error.h ../include/utils.h DESTINATION include)