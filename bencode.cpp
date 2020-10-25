// bencode.cpp : Defines the entry point for the application.
//

#include "bencode.h"
#include "bdict.h"
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

	stringstream test("i47434e4:testli56e5:yuioped3:cowi7856e4:spam4:eggse");

	auto i = decode<bencode::bdata>(test);
	std::visit([](const auto arg) { cout << arg << endl;}, i);

	auto t = decode<bdata>(test);
	std::visit([](const auto arg) { cout << arg << endl;}, t);

	auto l = decode<bdata>(test);
	std::visit([](const auto arg) { cout << arg << endl;}, l);

	auto d = decode<bdata>(test);
	std::visit([](const auto arg) { cout << arg << endl;}, d);

	// auto items = get<blist>(get<bdata>(l)).get_internal();

	// auto dict = decode<bdict>(test);

	// if (dict.index() == 0) { cout << get<string>(dict); }
	// else {
	// 	auto mapdict = get<bdict>(dict).get_internal();
	// 	cout << mapdict;
	// }
	// else { cout << (get<bdict>(dict).get_internal().begin()->first); }
	// auto parseItem = [](bdata &item) { cout << item.get_internal(); };
	// for_each(items.begin(), items.end(), parseItem);

	return 0;
}
