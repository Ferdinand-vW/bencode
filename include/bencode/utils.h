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

	// template <class A>
	// void traverse(bint bi, function<void(bencoding)> f) {
	// 	f(bi);
	// }

	// template <class A>
	// void traverse(bstring bs, function<void(bencoding)> f) {
	// 	f(bs);
	// }

	// void traverse(bdict bd, function<void(bencoding)> f) {
	// 	f(bd);

	// 	auto mp = bd.value();
	// 	for(auto kvp : mp) {
	// 		auto bdat = *kvp.second.get();
	// 		f(bdat.value());
	// 	}

	// }

	// optional<std::enable_if_t< !std::is_same< A, bool >::value, A >> 
}