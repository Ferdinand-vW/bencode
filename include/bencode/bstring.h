#pragma once

#include "btypes.h"
#include <string>
#include <sstream>

using namespace std;

namespace bencode {

	class bstring {
		vector<char> s;
	public:
		bstring(vector<char> ss) : s(ss) {};

		string display_type();
		vector<char> value() const { return s; }
		string to_string() const { return string(s.begin(),s.end()); }

		friend ostream& operator<<(ostream& os, bstring& bs);
		friend bool operator<(bstring b1,bstring b2);
	};
}
