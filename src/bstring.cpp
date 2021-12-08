#include "bencode/bencode.h"

namespace bencode {
    std::string bstring::display_type() {
        return "bstring";
    }

    std::ostream& operator<<(std::ostream& os,const bstring& bs) {
        os << bs.to_string();

        return os;
    }
			
    bool operator<(bstring b1,bstring b2) {
        return b1.value() < b2.value();
    }
}