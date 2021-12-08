#pragma once

#include <ostream>
#include "btypes.h"
// #include "binterface.h"

using namespace std;

namespace bencode {

	class bint {
		long long i;
	public:
		bint(long long j) : i(j) {};

		long long value() const { return i; }

		std::string display_type();

		friend std::ostream& operator<<(std::ostream&, const bint&);
	};
}