#pragma once

#include <string>
#include <sstream>

using namespace std;

namespace bencode {

	class bstring {
		string s;
	public:
			bstring(string ss) : s(ss) {};
	};

	bstring decode(stringstream& ss);
}
