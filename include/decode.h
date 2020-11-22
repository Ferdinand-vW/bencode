#pragma once

#include <string>
#include <map>
#include <map>
#include <sstream>
#include "bstring.h"
#include "bdict.h"
#include "bint.h"
#include "blist.h"
#include <variant>
#include "utils.h"

using namespace std;

namespace bencode
{
	template<class T>
	either<T> decode(stringstream& ss);
	template<>
	either<bdata> decode<bdata>(stringstream& ss);
	// template<>
	// outcome<bdata> decode<bdata>(stringstream& ss);

	bool peek_bint(stringstream& ss);
	bool peek_bstring(stringstream& ss);
	bool peek_blist(stringstream& ss);
	bool peek_bdict(stringstream& ss);
}