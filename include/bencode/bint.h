#pragma once

#include <ostream>
#include "btypes.h"
// #include "binterface.h"

using namespace std;

namespace bencode {

	class bint {
		int i;
	public:
		bint(int j) : i(j) {};

		int value() const { return i; }

		string display_type();

		friend ostream& operator<<(ostream&, const bint&);
	};
}