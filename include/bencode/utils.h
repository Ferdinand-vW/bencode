#pragma once

#include <new>
#include <variant>
#include <functional>
#include "iostream"

using namespace std;

namespace bencode {

	template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
	template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

	template <typename A,typename T>
	optional<A> try_get(T&& v) {
		if (holds_alternative<A>(std::forward<T>(v))) {
			return get<A>(std::forward<T>(v));
		}
		else { return {}; }
	}
}