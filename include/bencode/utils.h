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

	template <typename... As,typename A>
	optional<A> try_get(variant<A,As...> v) {
		return get<A>(v);
	}
	template <typename A>
	optional<A> try_get(variant<A> v) {
		return get<A>(v);
	}
	template <typename B,typename A,typename... As>
	optional<A> try_get(variant<B,As...> v) {
		return try_get(variant<As...>(v));
	}
	template <typename A,typename B>
	optional<A> try_get(variant<B> v) {
		return {};
	}


}