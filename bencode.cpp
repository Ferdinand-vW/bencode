// bencode.cpp : Defines the entry point for the application.
//

#include "bencode.h"
#include "decode.h"
#include "bstring.h"
#include <ostream>
#include <sstream>
#include "utils.h"
#include <variant>
#include "btypes.h"

using namespace std;
using namespace bencode;

int main()
{
	cout << "Hello CMake." << endl;

	stringstream test("i47434e4:test");

	auto d = bencode::decode<bencode::bdata>(test);

	cout << get<bint>(get<bdata>(d)).get_internal() << endl;

	auto t = decode<bdata>(test);

	cout << get<bstring>(get<bdata>(t)).get_internal();

	return 0;
}
