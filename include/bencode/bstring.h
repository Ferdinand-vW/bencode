#pragma once

#include "btypes.h"
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

namespace bencode {

	class bstring {
		vector<char> v;
	public:
		bstring(vector<char> vs) : v(vs) {};
		bstring(string s) {
			v.reserve(s.size());
			std::copy(s.begin(),s.end(),v.begin());
		 }

		string display_type();
		vector<char> value() const { return v; }
		string to_string() const { return string(v.begin(),v.end()); }

		friend ostream& operator<<(ostream& os, bstring& bs);
		friend bool operator<(bstring b1,bstring b2);
	};
}
