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
		map<bstring,bdata> get_internal() { return key_values; }
	};
}