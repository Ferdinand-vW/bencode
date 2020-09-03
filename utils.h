#pragma once

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
}