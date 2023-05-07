#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <vector>

#include "bencode/bdata.h"
#include "bencode/btypes.h"

namespace bencode {
	class blist {
		std::vector<bdata> m_items;

	public:
		blist(std::vector<bdata> &&items) : m_items(std::move(items)) {};
		const std::vector<bdata>& values() const;
		std::vector<bdata> values();

		std::string display_type();
		
		friend std::ostream& operator<<(std::ostream& os, const blist &bl);
	};
}