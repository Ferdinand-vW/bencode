#pragma once

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include "btypes.h"
using namespace std;

namespace bencode
{
	class bdict {
		map<string, bdata> key_values;
	public:
		bdict(map<string, bdata> kv) : key_values(kv) {};
	};
}