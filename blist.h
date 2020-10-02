#pragma once

#include <ostream>
#include <vector>
#include "btypes.h"

using namespace std;

namespace bencode {
	class blist {
		vector<bdata> items;

	public:
		blist(vector<bdata> _items) : items(_items) {};

		const vector<bdata> get_internal() { return items; }

		friend ostream& operator<<(ostream& os, const blist &bl) {
			// os << bl.items;

			return os;
		}
	};
}