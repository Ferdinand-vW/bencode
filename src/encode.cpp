#include <algorithm>
#include <variant>
#include <string>

#include "bencode/bencode.h"

namespace bencode {

    template<>
    std::string encode<bint>(bint bi) {
        return "i" + std::to_string(bi.value()) + "e";
    }

    template<>
    std::string encode<bstring>(bstring bs) {
        auto s = bs.value();
        return std::to_string(s.size()) + ":" + bs.to_string();
    }

    template<>
    std::string encode<bdict>(bdict bd) {
        auto kvs = bd.key_values();
        vector<pair<bstring,bdata>> entries (kvs.begin(),kvs.end());
        
        // sort elements by key
        sort(entries.begin(),entries.end(),[](auto &p1, auto &p2) { return p1.first < p2.first; });

        string s("");
        for(auto p : entries) {
            // encode key and value
            s += encode<bstring>(p.first) + encode<bdata>(p.second);
        }


        return "d" + s + "e";
    }

    template<>
    std::string encode<blist>(blist bl) {
        auto items = bl.value();
        std::string s = "";
        for(auto i : items) {
            s += encode<bdata>(i);
        }
        return "l" + s + "e"; 
    }

    template<>
    std::string encode<bdata>(bdata b) {
        auto benc = b.value();
        return 
            std::visit(overloaded { 
                [](bint &bi) { return encode<bint>(bi); },
                [](bstring &bs) { return encode<bstring>(bs); },
                [](bdict &bd) { return encode<bdict>(bd); },
                [](blist &bl) { return encode<blist>(bl); }
            },benc);
    }
}