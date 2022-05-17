#include "bencode/blist.h"
#include "bencode/bdata.h"

namespace bencode {
    string blist::display_type() {
        return "blist";
    }

    ostream& operator<<(ostream& os,const blist &bl) {
        auto items = bl.value();
        os << "[";
        bool first = true;
        for (const auto &item : items) {
            if (first) { first = false; }
            else { os << ", "; }
            os << item;
        }

        os << "]";

        return os;
    }
}