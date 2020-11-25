// bencode.cpp : Defines the entry point for the application.
//

#include "bencode.h"
#include "bdict.h"
#include "decode.h"
#include "encode.h"
#include "bstring.h"
#include <algorithm>
#include <ostream>
#include <sstream>
#include <string>
#include "utils.h"
#include <variant>
#include "btypes.h"
#include "bdata.h"

using namespace std;
using namespace bencode;

int main()
{
	stringstream test("i47434e4:testli56e5:yuioped3:cowi7856e4:spam4:eggse");

	auto i = decode<bencode::bdata>(test);
	if (i.has_value()) { cout << i.value() << endl; }
	else   { cout << i.error().message() << endl; }

	cout << encode(i.value()) << endl;;

	auto t = decode<bencode::bdata>(test);
	if (t.has_value()) 
		   { cout << t.value() << endl; }
	else   { cout << t.error().message() << endl; }

	cout << encode(t.value()) << endl;;

	auto l = decode<bdata>(test);
	if (l.has_value()) 
		   { cout << l.value() << endl; }
	else   { cout << l.error().message() << endl; }

	cout << encode(l.value()) << endl;

	auto d = decode<bdata>(test);
	if (d.has_value()) 
		   { cout << d.value() << endl; }
	else   { cout << d.error().message() << endl; }

	cout << encode(d.value()) << endl;

	return 0;
}
