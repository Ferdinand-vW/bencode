#pragma once

#include <string>
#include <map>
#include <map>
#include <sstream>
#include "bstring.h"
#include "bdict.h"

using namespace std;

namespace bencode
{
	template <class T>
	class decoder {
	public:
		T decode(stringstream& ss);
	};

	bstring decoder<bstring>::decode(stringstream& ss);
	bdict decoder<bdict>::decode(stringstream& ss);
}