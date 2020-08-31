// bencode.cpp : Defines the entry point for the application.
//

#include "bencode.h"
#include "bstring.h"
#include <sstream>

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	stringstream test("4:spam3:test");
	cout << bencode::decode(test);

	return 0;
}
