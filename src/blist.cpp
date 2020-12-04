#include "bencode/blist.h"
#include "bencode/bstring.h"
#include "bencode/bint.h"
#include "bencode/bdict.h"
#include "bencode/bdata.h"
#include "bencode/utils.h"

namespace bencode {
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