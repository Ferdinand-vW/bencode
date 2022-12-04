#pragma once

#include "bstring.h"
#include "bdict.h"
#include "bint.h"
#include "blist.h"
#include "utils.h"

namespace bencode
{
	template<class T>
	either<T> decode(std::istream& ss);
	template<>
	either<bint> decode<bint>(std::istream& ss);
	template<>
	either<bstring> decode<bstring>(std::istream& ss);
	template<>
	either<blist> decode<blist>(std::istream& ss);
	template<>
	either<bdict> decode<bdict>(std::istream& ss);
	template<>
	either<bdata> decode<bdata>(std::istream& ss);

	bool peek_bint(std::istream& ss);
	bool peek_bstring(std::istream& ss);
	bool peek_blist(std::istream& ss);
	bool peek_bdict(std::istream& ss);
}