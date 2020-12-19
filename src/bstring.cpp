#include "bencode/bencode.h"

namespace bencode {

    ostream& operator<<(ostream& os, bstring& bs) {
        os << bs.value();

        return os;
    }
			
    bool operator<(bstring b1,bstring b2) {
        return b1.value() < b2.value();
    }
}