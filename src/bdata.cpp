#include <variant>
#include "bencode/bdata.h"
#include "bencode/bint.h"
#include "bencode/bstring.h"
#include "bencode/bdict.h"
#include "bencode/blist.h"
#include "bencode/btypes.h"
#include "bencode/utils.h"

namespace bencode {

	bdata::bdata (const bint& b) : m_decoded(std::shared_ptr<bencoding>(new bencoding(bint(b)))) {}
	bdata::bdata (const bstring& b) : m_decoded(std::shared_ptr<bencoding>(new bencoding(bstring(b)))) {}
	bdata::bdata (const blist& b) : m_decoded(std::shared_ptr<bencoding>(new bencoding(blist(b)))) {}
	bdata::bdata (const bdict& b) : m_decoded(std::shared_ptr<bencoding>(new bencoding(bdict(b)))) {}

	std::optional<bint> bdata::get_bint() const
	{
		return try_get<bint>(*m_decoded);
	}

	std::optional<bstring> bdata::get_bstring() const
	{
		return try_get<bstring>(*m_decoded);
	}

	std::optional<blist> bdata::get_blist() const
	{
		return try_get<blist>(*m_decoded);
	}

	std::optional<bdict> bdata::get_bdict() const
	{
		return try_get<bdict>(*m_decoded);
	}

	std::string bdata::display_type() {
		return std::visit(overloaded { 
			[](bint &bi) { return bi.display_type(); },
			[](bstring &bs) { return bs.display_type(); },
			[](bdict &bd) { return bd.display_type(); },
			[](blist &bl) { return bl.display_type(); }
			}, *m_decoded.get());
	}

    std::ostream& operator<<(std::ostream &os,const bdata &bd) {
		auto benc = bd.value();
		std:visit([&os](auto &v) { os << v;}, *benc);

		return os;
	}
}