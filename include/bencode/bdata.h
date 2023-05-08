#pragma once

#include "bencode/bdict.h"
#include "bencode/bint.h"
#include "bencode/blist.h"
#include "bencode/bstring.h"
#include "bencode/btypes.h"
#include "bencode/utils.h"
#include <memory>
#include <optional>
#include <variant>

namespace bencode
{
class bdata
{
  public:
    using bencoding = std::variant<bint, bstring, bdict, blist>;

    const std::variant<bint, bstring, bdict, blist>& value() const
    {
        return m_decoded;
    }

    bdata(const bdata &bd);
    bdata &operator=(const bdata &) = default;
    bdata(const bint &b);
    bdata(const bstring &b);
    bdata(const blist &b);
    bdata(const bdict &b);

    std::optional<bint> get_bint() const;
    std::optional<bstring> get_bstring() const;
    std::optional<blist> get_blist() const;
    std::optional<bdict> get_bdict() const;

    std::string display_type() const;
    friend std::ostream &operator<<(std::ostream &, const bdata &);

    private:
        bencoding m_decoded;
};
} // namespace bencode