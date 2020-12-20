#pragma once

#include "btypes.h"
#include <string>
#include <sstream>

using namespace std;

namespace bencode {

	class bstring {
		string s;
	public:
		bstring(string ss) : s(ss) {};

		string display_type();
		string value() const { return s; }

		friend ostream& operator<<(ostream& os, bstring& bs);
		friend bool operator<(bstring b1,bstring b2);
	};
}
