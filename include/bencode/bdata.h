#pragma once

#include <memory>
#include <variant>
#include "bencode/btypes.h"
#include "bencode/bint.h"
#include "bencode/bstring.h"
#include "bencode/blist.h"
#include "bencode/bdict.h"
#include "bencode/utils.h"

namespace bencode {
    class bdata {
        bencode::bencoding m_decoded;

        public:
            const bencoding& value() const { return m_decoded; }
            std::optional<bint>    get_bint()    const { return try_get<bint>(m_decoded); }
            std::optional<bstring> get_bstring() const { return try_get<bstring>(m_decoded); }
            std::optional<blist>   get_blist()   const { return try_get<blist>(m_decoded); }
            std::optional<bdict>   get_bdict()   const { return try_get<bdict>(m_decoded); }

            bdata (const bencoding &&pd) : m_decoded(std::move(pd)) {};
            bdata (const bencoding &pd)  : m_decoded(pd) {};
            bdata (const bint      &&pd) : m_decoded(std::move(pd)) {};
            bdata (const bint      &pd)  : m_decoded(pd) {};
            bdata (const bstring   &&pd) : m_decoded(std::move(pd)) {};
            bdata (const bstring   &pd)  : m_decoded(pd) {};
            bdata (const blist     &&pd) : m_decoded(std::move(pd)) {};
            bdata (const blist     &pd)  : m_decoded(pd) {};
            bdata (const bdict     &&pd) : m_decoded(std::move(pd)) {};
            bdata (const bdict     &pd)  : m_decoded(pd) {};

            string display_type();

            friend std::ostream& operator<<(std::ostream&,const bdata&);
    };
}