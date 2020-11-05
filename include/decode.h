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
#include <boost/outcome/outcome.hpp>

using namespace std;
using namespace boost::outcome_v2;

namespace bencode
{
	template<class T>
	outcome<T> decode(stringstream& ss);
	template<>
	outcome<bdata> decode<bdata>(stringstream& ss);
	// template<>
	// outcome<bdata> decode<bdata>(stringstream& ss);

	bool peek_bint(stringstream& ss);
	bool peek_bstring(stringstream& ss);
	bool peek_blist(stringstream& ss);
	bool peek_bdict(stringstream& ss);
}