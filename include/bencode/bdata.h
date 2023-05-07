#pragma once

#include <memory>
#include <optional>
#include <variant>
#include "bencode/btypes.h"
#include "bencode/utils.h"

namespace bencode {
    class bdata {
        std::shared_ptr<bencode::bencoding> m_decoded;

        public:
            const bencoding* value() const { return m_decoded.get(); }

            bdata (std::shared_ptr<bencoding> &&pd) : m_decoded(std::move(pd)) {};
            bdata (const bdata&) = default;
            bdata (bdata&&) = default;
            bdata& operator=(const bdata &) = default;
            bdata& operator=(bdata &&) = default;
            bdata (const bint& b);
            bdata (const bstring& b);
            bdata (const blist& b);
            bdata (const bdict& b);

            std::optional<bint> get_bint() const;
            std::optional<bstring> get_bstring() const;
            std::optional<blist> get_blist() const;
            std::optional<bdict> get_bdict() const;

            std::string display_type();
            friend std::ostream& operator<<(std::ostream&, const bdata&);
    };
}