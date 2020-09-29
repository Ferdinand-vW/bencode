#pragma once

#include <string>
#include <sstream>

using namespace std;

namespace bencode {

	class bstring {
		string s;
	public:
			bstring(string ss) : s(ss) {};

			string get_internal() { return s; }
			
		friend bool operator<(bstring b1,bstring b2) {
			return b1.get_internal() < b2.get_internal();
		}	

	};
}
