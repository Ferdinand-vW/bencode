// bencode.cpp : Defines the entry point for the application.
//


#include <algorithm>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <variant>
#include "bencode/btypes.h"
#include "bencode/utils.h"

#include "bencode/decode.h"
#include "bencode/encode.h"

;
using namespace bencode;

template <class T>
void print_val(const T &t) {
	std::cout << "val: " << t << std::endl;
}

int main()
{
	std::stringstream test("d3:cowi7856e4:spam4:eggse");
	
	auto i = decode<bencode::bdata>(test);
	std::cout << encode(i.value()) << std::endl;

	return 0;
}
