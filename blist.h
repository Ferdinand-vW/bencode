#pragma once

#include <vector>
#include "btypes.h"

using namespace std;

namespace bencode {
	class blist {
		vector<bdata> items;

	public:
		blist(vector<bdata> _items) : items(_items) {};
	};
}