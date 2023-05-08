#include <algorithm>
#include <variant>
#include <string>

#include "bencode/bencode.h"

namespace bencode {

    template<>
    std::string encode<bint>(const bint &bi) {
        return "i" + std::to_string(bi.value()) + "e";
    }

    template<>
    std::string encode<bstring>(const bstring &bs) {
        auto s = bs.value();
        return std::to_string(s.size()) + ":" + bs.to_string();
    }

    template<>
    std::string encode<bdict>(const bdict &bd) {
        auto& kvs = bd.key_values();
        std::vector<std::pair<bstring,std::shared_ptr<bdata>>> entries (kvs.begin(),kvs.end());
        
        // sort elements by key
        sort(entries.begin(),entries.end(),[](auto &p1, auto &p2) { return p1.first < p2.first; });

        std::string s("");
        for(const auto& p : entries) {
            // encode key and value
            s += encode<bstring>(p.first) + encode<bdata>(*p.second.get());
        }


        return "d" + s + "e";
    }

    template<>
    std::string encode<blist>(const blist &bl) {
        auto items = bl.values();
        std::string s = "";
        for(const auto& i : items) {
            s += encode<bdata>(i);
        }
        return "l" + s + "e"; 
    }

    template<>
    std::string encode<bdata>(const bdata &b) {
        auto benc = b.value();
        return 
            std::visit(overloaded { 
                [](const bint &bi) { return encode<bint>(bi); },
                [](const bstring &bs) { return encode<bstring>(bs); },
                [](const bdict &bd) { return encode<bdict>(bd); },
                [](const blist &bl) { return encode<blist>(bl); }
            },benc);
    }
}