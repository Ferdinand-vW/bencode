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

int main()
{
	stringstream test("d3:cowi7856e4:spam4:eggse");
	
	auto i = decode<bencode::bdata>(test);
	// if (i.has_value()) { cout << i.value() << endl; }
	// else   { cout << i.error().message() << endl; }
	bdata bdat = i.value();
	
	auto f = [](auto v) { 
		std::visit(overloaded {
			[](int &i)    { cout << "val: " << i << endl;},
			[](string &s) { cout << "val: " << s << endl;},
			[](bdata &bd) {return;},
			[](auto &p)   { cout << "key: " << p.first << endl; }
			}, v); 
		};
	bdat.traverse(f);

	cout << encode(i.value()) << endl;

	return 0;
}
