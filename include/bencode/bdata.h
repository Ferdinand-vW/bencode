#pragma once

#include <memory>
#include "btypes.h"
#include "bint.h"
#include "bstring.h"
#include "blist.h"
#include "bdict.h"
#include "utils.h"

namespace bencode {
    class bdata {
        shared_ptr<bencode::bencoding> decoded;

        public:
            bencoding value() const { return *decoded; }
            optional<bint>    get_bint()    const { return try_get<bint>(*decoded.get()); }
            optional<bstring> get_bstring() const { return try_get<bstring>(*decoded.get()); }
            optional<blist>   get_blist()   const { return try_get<blist>(*decoded.get()); }
            optional<bdict>   get_bdict()   const { return try_get<bdict>(*decoded.get()); }

            bdata (const bencoding &pd) : decoded(make_shared<bencoding>(pd)) {};
            bdata (const bint      &pd) : decoded(make_shared<bencoding>(pd)) {};
            bdata (const bstring   &pd) : decoded(make_shared<bencoding>(pd)) {};
            bdata (const blist     &pd) : decoded(make_shared<bencoding>(pd)) {};
            bdata (const bdict     &pd) : decoded(make_shared<bencoding>(pd)) {};

            string display_type() {
                auto v = *decoded.get();
                return std::visit(overloaded { 
                    [](bint &bi) { return "bint"; },
                    [](bstring &bs) { return "bstring"; },
                    [](bdict &bd) { return "bdict"; },
                    [](blist &bl) { return "blist"; }
                    },v);
            }

            friend ostream& operator<<(ostream& os,const bdata &bd);
    };
}