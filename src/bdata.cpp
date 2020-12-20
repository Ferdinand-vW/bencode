#include <variant>
#include "bencode/bencode.h"
#include "bencode/btypes.h"

namespace bencode {

	string bdata::display_type() {
		auto v = *decoded.get();
		return std::visit(overloaded { 
			[](bint &bi) { return bi.display_type(); },
			[](bstring &bs) { return bs.display_type(); },
			[](bdict &bd) { return bd.display_type(); },
			[](blist &bl) { return bl.display_type(); }
			},v);
	}

    ostream& operator<<(ostream &os,const bdata &bd) {
		auto benc = bd.value();
		std:visit([&os](auto &v) { os << v;}, benc);

		return os;
	}
}