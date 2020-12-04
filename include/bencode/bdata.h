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
            optional<bint> get_bint() const { return try_get<bint>(*decoded).get() }

            bdata (const bencoding &pd) : decoded(make_shared<bencoding>(pd)) {};
            bdata (const bint      &pd) : decoded(make_shared<bencoding>(pd)) {};
            bdata (const bstring   &pd) : decoded(make_shared<bencoding>(pd)) {};
            bdata (const blist     &pd) : decoded(make_shared<bencoding>(pd)) {};
            bdata (const bdict     &pd) : decoded(make_shared<bencoding>(pd)) {};

            friend ostream& operator<<(ostream& os,const bdata &bd);
    };
}