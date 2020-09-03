#pragma once

#include <string>
#include <map>
#include <map>
#include <sstream>
#include "bstring.h"
#include "bdict.h"
#include "bint.h"
#include "blist.h"
#include "bdata.h"
#include <variant>
#include "utils.h"

using namespace std;

namespace bencode
{
	/*template <class T>
	class decoder {
	public:
		static variant<string,T> decode(stringstream& ss);
		static bool isInt(stringstream& ss);
		static bool isString(stringstream& ss);
		static bool isDict(stringstream& ss);
		static bool isList(stringstream& ss);
	};

	std::variant<string,bstring> decoder<bstring>::decode(stringstream& ss);


	variant<string,bint> decoder<bint>::decode(stringstream& ss);
	variant<string,blist> decoder<blist>::decode(stringstream& ss);
	variant<string,bdict> decoder<bdict>::decode(stringstream& ss);
	variant<string,bdata> decoder<bdata>::decode(stringstream& ss);*/

	template<class T>
	variant<string, T> decode(stringstream& ss);
}