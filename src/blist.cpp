#include "bencode/blist.h"
#include "bencode/bdata.h"

namespace bencode {
    std::string blist::display_type() {
        return "blist";
    }

    const std::vector<bdata>& blist::values() const
    {
        return m_items;
    }

    std::ostream& operator<<(std::ostream& os,const blist &bl) {
        auto items = bl.values();
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