#pragma once

#include <string>
#include <sstream>

using namespace std;

namespace bencode {

	class bstring {
		string s;
	public:
			bstring(string ss) : s(ss) {};

		string value() const { return s; }

		friend ostream& operator<<(ostream& os, bstring& bs) {
			os << bs.value();

			return os;
		}
			
		friend bool operator<(bstring b1,bstring b2) {
			return b1.value() < b2.value();
		}	

	};
}
