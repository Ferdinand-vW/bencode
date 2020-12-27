#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <vector>
#include "btypes.h"
// #include "binterface.h"

using namespace std;

namespace bencode {
	class blist {
		vector<bdata> items;

	public:
		blist(vector<bdata> _items) : items(_items) {};
		vector<bdata> value() const { return items; }

		string display_type();
		
		friend ostream& operator<<(ostream& os, const blist &bl);
	};
}