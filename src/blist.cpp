#include "blist.h"
#include "bstring.h"
#include "bint.h"
#include "bdict.h"
#include "bdata.h"
#include "utils.h"

namespace bencode {
    ostream& operator<<(ostream& os,const blist &bl) {
        auto items = bl.get_internal();
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