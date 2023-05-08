#include "bencode/blist.h"
#include "bencode/bdata.h"

namespace bencode {
    blist::blist(const std::vector<bdata> &items) 
    {
        m_items.reserve(items.size());
        for (const auto& i : items)
        {
            m_items.emplace_back(std::make_shared<bdata>(i));
        }
    }

    std::string blist::display_type() const {
        return "blist";
    }

    std::vector<bdata> blist::values() const
    {
        std::vector<bdata> out;
        out.reserve(m_items.size());
        for (auto i : m_items)
        {
            out.push_back(*i.get());
        }
        return out;
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