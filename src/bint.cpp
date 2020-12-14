#include "bencode/bencode.h"

namespace bencode {
    void bint::traverse(function<void(bencoding_prim)> f) {
			f(i);
	}

    ostream& operator<<(ostream& os, const bint& bi) {
			os << bi.value();

			return os;
	}
}