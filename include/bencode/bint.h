#pragma once

#include <ostream>
#include "bencode/btypes.h"

namespace bencode {

	class bint {
		int64_t i;
	public:
		bint(int64_t j) : i(j) {}
		bint(const bint& bi) : i(bi.i) {}
		int64_t value() const { return i; }

		std::string display_type() const;

		friend std::ostream& operator<<(std::ostream&, const bint&);
	};
}