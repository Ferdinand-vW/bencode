#include "bencode/bencode.h"

namespace bencode {

	string bint::display_type() {
		return "bint";
	}

    ostream& operator<<(ostream& os, const bint& bi) {
		os << bi.value();
		return os;
	}
}