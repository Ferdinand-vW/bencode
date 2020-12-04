#pragma once

#include "bstring.h"
#include "bdict.h"
#include "bint.h"
#include "blist.h"
#include "utils.h"

using namespace std;

namespace bencode
{
	template<class T>
	either<T> decode(istream& ss);
	template<>
	either<bdata> decode<bdata>(istream& ss);

	bool peek_bint(istream& ss);
	bool peek_bstring(istream& ss);
	bool peek_blist(istream& ss);
	bool peek_bdict(istream& ss);
}