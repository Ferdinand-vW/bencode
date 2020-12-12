#pragma once

#include <new>
#include <variant>
#include <functional>
#include "iostream"
#include "btypes.h"
#include "bdict.h"
#include "blist.h"
#include "bint.h"
#include "bstring.h"

using namespace std;

namespace bencode {

	template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
	template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

	template <class A,class... As>
	optional<A> try_get(variant<As...> v) {
		if (holds_alternative<A>(v)) {
			return get<A>(v);
		}
		else { return {}; }
	}

	// optional<std::enable_if_t< !std::is_same< A, bool >::value, A >> 
}