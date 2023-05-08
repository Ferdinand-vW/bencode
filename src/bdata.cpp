#include "bencode/bdata.h"
#include "bencode/bdict.h"
#include "bencode/bint.h"
#include "bencode/blist.h"
#include "bencode/bstring.h"
#include "bencode/btypes.h"
#include "bencode/utils.h"

namespace bencode
{

bdata::bdata(const bdata &bd) : m_decoded(bd.m_decoded)
{
}

bdata::bdata(const bint &b) : m_decoded(b)
{
}

bdata::bdata(const bstring &b) : m_decoded(b)
{
}

bdata::bdata(const blist &b) : m_decoded(b)
{
}

bdata::bdata(const bdict &b) : m_decoded(b)
{
}

std::optional<bint> bdata::get_bint() const
{
    return try_get<bint>(m_decoded);
}

std::optional<bstring> bdata::get_bstring() const
{
    return try_get<bstring>(m_decoded);
}

std::optional<blist> bdata::get_blist() const
{
    return try_get<blist>(m_decoded);
}

std::optional<bdict> bdata::get_bdict() const
{
    return try_get<bdict>(m_decoded);
}

std::string bdata::display_type() const
{
    return std::visit(overloaded{[](const bint &bi) { return bi.display_type(); },
                                 [](const bstring &bs) { return bs.display_type(); },
                                 [](const bdict &bd) { return bd.display_type(); },
                                 [](const blist &bl) { return bl.display_type(); }},
                      m_decoded);
}

std::ostream &operator<<(std::ostream &os, const bdata &bd)
{
    std::visit(overloaded{[&os](const bint &v) { os << "bint", os << v; },
                          [&os](const bstring &v) { os << "bstring", os << v; },
                          [&os](const blist &v) { os << "blist", os << v; },
                          [&os](const bdict &v) { os << "bdict", os << v; }},
               bd.m_decoded);

    return os;
}
} // namespace bencode