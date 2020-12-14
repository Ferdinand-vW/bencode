#include <variant>
#include "bencode/blist.h"
#include "bencode/bencode.h"

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

	void bdata::traverse(function<void(bencoding)> f,function<void(flat_bencoding)> g) {
        auto b = *decoded.get();
		f(b);
		std::visit(overloaded {
			[](bint &bi)    { g(bi); },
			[](bstring &bs) { g(bi); },
			[f](blist &bl)  { bl.traverse(f); },
			[f](bdict &bd)  { bd.traverse(f); },
		}, b);
    }

	        //     std::visit(overloaded { 
            //     [](bint &bi) { return encode<bint>(bi); },
            //     [](bstring &bs) { return encode<bstring>(bs); },
            //     [](bdict &bd) { return encode<bdict>(bd); },
            //     [](blist &bl) { return encode<blist>(bl); }
            // },benc);

    ostream& operator<<(ostream &os,const bdata &bd) {
		auto benc = bd.value();
		std:visit([&os](auto &v) { os << v;}, benc);

		return os;
	}
}