# bencode

Library for encoding and decoding using the Bencode protocol written in C++. Primarily used by BitTorrent protocol for encoding and decoding of data exchanged between a peer and the tracker.

## Features
* Parses bencode strings to C++ classes
* Support for input and output streams
* Provides a safe api with error support

## Include in project

I will assume you're using CMake

1. Clone/download this repository into your own project folder
2. Set CMake variable pointing to the include directory
```cmake
set(BENCODE_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/libs/bencode/include)
```
3. Add bencode as a subdirectory to your project
```cmake
add_subdirectory(libs/bencode)
```
4. Link the include directories to a target
```cmake
target_include_directors(MyProj PUBLIC ${BENCODE_INCLUDE_DIR})
```
5. Link the bencode library
```cmake
target_link_libraries(MyProj bencode)
``` 


## Example usage

```cpp

#include <bencode/bencode.h>

stringstream test("d3:cowi7856e4:spam4:eggse");
	
auto i = decode<bencode::bdata>(test);
cout << encode(i.value()) << endl;
```

