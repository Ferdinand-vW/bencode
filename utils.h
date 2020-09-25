#pragma once

#include <new>
#include <variant>
#include <functional>
#include "iostream"

using namespace std;

namespace bencode {

	template<class A,class B, class S>
	variant<S, B> flatMap(variant<S,B> var,function<variant<S,B>(A)> f) {
			auto alternative = holds_alternative<S>(var);

			if (alternative) { return var; }
			else { return f(get<A>(var)); }
		}

	template<class A,class S>
	variant<S,A> alternative(variant<S,A> a,variant<S,A> b) {
		auto aBool = holds_alternative<A>(a);
		auto bBool = holds_alternative<A>(b);

		if (aBool || !bBool) { return a; }
		else { return b; }
	}

	template<class A,class B,class S>
	variant<S,B> map(variant<S,A> v,function<B(A)> f) {
		auto alt = holds_alternative<A>(v);

		if(alt) { return f(get<A>(v)); }
		else { return get<S>(v); }
	}

	
}