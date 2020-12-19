#include <variant>
#include "bencode/bencode.h"
#include "bencode/btypes.h"

namespace bencode {

	string bdata::display_type() {
		auto v = *decoded.get();
		return std::visit(overloaded { 
			[](bint &bi) { return "bint"; },
			[](bstring &bs) { return "bstring"; },
			[](bdict &bd) { return "bdict"; },
			[](blist &bl) { return "blist"; }
			},v);
	}

    ostream& operator<<(ostream &os,const bdata &bd) {
		auto benc = bd.value();
		std:visit([&os](auto &v) { os << v;}, benc);

		return os;
	}
}