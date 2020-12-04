#pragma once

#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "btypes.h"

using namespace std;

namespace bencode
{
	class bdict {
		map<bstring, shared_ptr<bdata>> key_values;
	public:
		bdict(map<bstring, shared_ptr<bdata>> kv) : key_values(kv) {};

		map<bstring, shared_ptr<bdata>> value() const {
			return key_values;
		}

		friend ostream& operator<<(ostream& os, const bdict &bd);
	};
}