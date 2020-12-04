#pragma once

#include <string>
#include <sstream>

using namespace std;

namespace bencode {

	class bstring {
		string s;
	public:
			bstring(string ss) : s(ss) {};

		string get_internal() const { return s; }

		friend ostream& operator<<(ostream& os, bstring& bs) {
			os << bs.get_internal();

			return os;
		}
			
		friend bool operator<(bstring b1,bstring b2) {
			return b1.get_internal() < b2.get_internal();
		}	

	};
}
