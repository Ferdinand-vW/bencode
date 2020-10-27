#pragma once

#include <ostream>
#include "btypes.h"

using namespace std;

namespace bencode {

	class bint {
		int i;
	public:
		bint(int j) : i(j) {};

		int get_internal() const { return i; }

		friend ostream& operator<<(ostream& os, const bint& bi) {
			os << bi.get_internal();

			return os;
		}
	};
}