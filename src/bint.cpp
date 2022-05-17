#include "bencode/bint.h"

namespace bencode {

	std::string bint::display_type() const {
		return "bint";
	}

    std::ostream& operator<<(std::ostream& os, const bint& bi) {
		os << bi.value();
		return os;
	}
}