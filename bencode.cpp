// bencode.cpp : Defines the entry point for the application.
//

#include "bencode.h"
#include "bstring.h"
#include <sstream>
#include "utils.h"
#include <variant>

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	stringstream test("4:spam3:test");
	function<variant<bool,int>(int)> f = [](auto a) { return a + 1; };
	cout << get<int>(bencode::flatMap(variant<bool, int>(2),f)); //bencode::decode(test);

	return 0;
}
