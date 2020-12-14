#include "bencode/bdata.h"
#include "bencode/blist.h"
#include "bencode/bint.h"
#include "bencode/bdict.h"
#include "bencode/bstring.h"
#include "bencode/utils.h"

namespace bencode {

    string bdict::display_type() {
        return "bdict";
    }

    void bdict::traverse(function<void(bencoding_prim)> f) {
        for(auto kvp : key_values) {
            std::pair<bstring,bdata> p(kvp.first, *kvp.second.get());
            f(p);
            kvp.second.get()->traverse(f);
        }
    }

    ostream& operator<<(ostream& os, const bdict &bd) {
        auto kvs = bd.value();
        os << "{";

        bool first = true;
        for (const auto& kv : kvs) {
            
            if (first) { first = false; }
            else { os << ", "; } // add comma between items

            os << kv.first.value() + " => ";
            os << (*kv.second);
        }

        os << "}";

        return os;
	}
}