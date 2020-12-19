#pragma once

#include <new>
#include <variant>
#include <functional>
#include "iostream"

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
}