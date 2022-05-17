#pragma once

#include <ostream>
#include "bencode/btypes.h"

using namespace std;

namespace bencode {

	class bint {
		int64_t i;
	public:
		bint(int64_t j) : i(j) {};

		int64_t value() const { return i; }

		std::string display_type() const;

		friend std::ostream& operator<<(std::ostream&, const bint&);
	};
}