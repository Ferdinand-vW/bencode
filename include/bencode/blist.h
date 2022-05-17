#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <vector>

#include "bencode/btypes.h"

using namespace std;

namespace bencode {
	class blist {
		vector<bdata> m_items;

	public:
		blist(vector<bdata> &&items) : m_items(std::move(items)) {};
		blist(vector<bdata> &items) : m_items(items) {};
		vector<bdata> value() const { return m_items; }

		string display_type();
		
		friend ostream& operator<<(ostream& os, const blist &bl);
	};
}