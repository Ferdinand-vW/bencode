#include "encode.h"
#include "btypes.h"
#include "bint.h"
#include "bstring.h"
#include "blist.h"
#include "bdict.h"
#include "bdata.h"
#include "utils.h"
#include <variant>
#include <string>

namespace bencode {

    template<>
    std::string encode<bint>(bint bi) {
        return "int";
    }

    template<>
    std::string encode<bstring>(bstring bs) {
        return "string";
    }

    template<>
    std::string encode<bdict>(bdict bd) {
        return "dict";
    }

    template<>
    std::string encode<blist>(blist bl) {
        return "list";
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