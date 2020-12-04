#include "bencode/bdata.h"
#include "bencode/blist.h"
#include "bencode/bint.h"
#include "bencode/bdict.h"
#include "bencode/bstring.h"
#include "bencode/utils.h"

namespace bencode {

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