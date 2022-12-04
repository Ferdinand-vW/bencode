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

            std::string display_type();
            friend std::ostream& operator<<(std::ostream&, const bdata&);
    };
}