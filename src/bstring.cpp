#include "bencode/bstring.h"

namespace bencode {
    std::string bstring::display_type() const {
        return "bstring";
    }

    std::ostream& operator<<(std::ostream& os,const bstring& bs) {
        os << bs.to_string();

        return os;
    }
			
    bool operator<(const bstring &b1,const bstring &b2) {
        return b1.value() < b2.value();
    }
}