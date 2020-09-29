// bencode.cpp : Defines the entry point for the application.
//

#include "bencode.h"
#include "decode.h"
#include "bstring.h"
#include <algorithm>
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

	stringstream test("i47434e4:testli56e:5:yuioped3:cow3:moo4:spam4:eggse");

	// bdata bd = decode(test);

	auto d = bencode::decode<bencode::bdata>(test);

	cout << get<bint>(get<bdata>(d)).get_internal() << endl;

	auto t = decode<bdata>(test);
	cout << t.index() << endl;
	cout << get<bstring>(get<bdata>(t)).get_internal() << endl;

	auto l = decode<bdata>(test);
	
	auto items = get<blist>(get<bdata>(l)).get_internal();

	auto dict = decode<bdict>(test);

	if (dict.index() == 0) { cout << get<string>(dict); }
	// else { cout << (get<bdict>(dict).get_internal().begin()->first); }
	// auto parseItem = [](bdata &item) { cout << item.get_internal(); };
	// for_each(items.begin(), items.end(), parseItem);

	return 0;
}
