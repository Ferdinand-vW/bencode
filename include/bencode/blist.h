#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <vector>

#include "bencode/btypes.h"

namespace bencode {
	class bdata;
	class blist {
		std::vector<std::shared_ptr<bdata>> m_items;

	public:
		blist(const std::vector<bdata> &items);
		blist(const std::vector<std::shared_ptr<bdata>> &items) : m_items(items) {};
		std::vector<bdata> values() const;

		std::string display_type() const;
		
		friend std::ostream& operator<<(std::ostream& os, const blist &bl);
	};
}