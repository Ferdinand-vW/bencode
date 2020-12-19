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

#include "bencode/bencode.h"

using namespace std;
using namespace bencode;

template <class T>
void print_val(const T &t) {
	cout << "val: " << t << endl;
}

int main()
{
	stringstream test("d3:cowi7856e4:spam4:eggse");
	
	auto i = decode<bencode::bdata>(test);
	cout << encode(i.value()) << endl;

	return 0;
}
