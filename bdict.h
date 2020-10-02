#pragma once

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include "bstring.h"
#include "btypes.h"
using namespace std;

namespace bencode
{
	class bdict {
		map<bstring, bdata> key_values;
	public:
		bdict(map<bstring, bdata> kv) : key_values(kv) {};

		map<bstring, bdata> get_internal() const {
			return key_values;
		}

		friend ostream& operator<<(ostream& os, const bdict& bd) {
			// for (const auto& kv : bd.get_internal()) {
			// 	// os << kv.first.get_internal();
			// }

			return os;
		}
	};
}