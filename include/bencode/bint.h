#pragma once

#include <ostream>
#include "btypes.h"

using namespace std;

namespace bencode {

	class bint {
		int i;
	public:
		bint(int j) : i(j) {};

		int value() const { return i; }

		void traverse(function<void(bencoding_prim)> f);
		friend ostream& operator<<(ostream& os, const bint& bi);
	};
}