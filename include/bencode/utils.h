#pragma once

#include <optional>
#include <variant>
#include <functional>
#include <iostream>

namespace bencode {

	template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
	template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

	template <typename A,typename T>
	std::optional<A> try_get(T&& v) 
	{
		if (holds_alternative<A>(std::forward<T>(v))) {
			return get<A>(std::forward<T>(v));
		}
		else { return {}; }
	}
}