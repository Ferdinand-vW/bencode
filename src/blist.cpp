#include "bencode/bencode.h"

namespace bencode {
    void blist::traverse(function<void(bencoding_prim)> f) {
        for(auto i_ptr : items) {
            auto i_val = *i_ptr.get();
            f(i_val);
            i_val.traverse(f);
        }
    }

    ostream& operator<<(ostream& os,const blist &bl) {
        auto items = bl.value();
        os << "[";
        bool first = true;
        for (const auto item : items) {
            if (first) { first = false; }
            else { os << ", "; }
            os << (*item);
        }

        os << "]";

        return os;
    }
}