#include "blist.h"
#include "bint.h"
#include "bdict.h"
#include "bstring.h"
#include "utils.h"

namespace bencode {

    ostream& operator<<(ostream& os, const bdict &bd) {
        auto kvs = bd.get_internal();
        os << "{";

        bool first = true;
        for (const auto& kv : kvs) {
            
            if (first) { first = false; }
            else { os << ", "; } // add comma between items

            os << kv.first.get_internal() + " => ";
            os << (*kv.second);
        }

        os << "}";

        return os;
	}
}