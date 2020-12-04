#include <algorithm>
#include <variant>
#include <string>

#include "bencode/encode.h"
#include "bencode/btypes.h"
#include "bencode/bint.h"
#include "bencode/bstring.h"
#include "bencode/blist.h"
#include "bencode/bdict.h"
#include "bencode/bdata.h"
#include "bencode/utils.h"

namespace bencode {

    template<>
    std::string encode<bint>(bint bi) {
        return "i" + std::to_string(bi.get_internal()) + "e";
    }

    template<>
    std::string encode<bstring>(bstring bs) {
        auto s = bs.get_internal();
        return std::to_string(s.length()) + ":" + s;
    }

    template<>
    std::string encode<bdict>(bdict bd) {
        auto kvPtrs = bd.get_internal();
        std::string s = "";

        for(auto kv : kvPtrs) {
            s += encode<bstring>(kv.first) + encode<bdata>(*kv.second); 
        }
        return "d" + s + "e";
    }

    template<>
    std::string encode<blist>(blist bl) {
        auto items = bl.get_internal();
        std::string s = "";
        for(auto i : items) {
            s += encode<bdata>(*i);
        }
        return "l" + s + "e"; 
    }

    template<>
    std::string encode<bdata>(bdata b) {
        auto benc = b.get_internal();
        return 
            std::visit(overloaded { 
                [](bint &bi) { return encode<bint>(bi); },
                [](bstring &bs) { return encode<bstring>(bs); },
                [](bdict &bd) { return encode<bdict>(bd); },
                [](blist &bl) { return encode<blist>(bl); }
            },benc);
    }
}