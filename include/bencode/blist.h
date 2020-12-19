#pragma once

#include <ostream>
#include <vector>
#include "btypes.h"
// #include "binterface.h"

using namespace std;

namespace bencode {
	class blist {
		vector<shared_ptr<bdata>> items;

	public:
		blist(vector<shared_ptr<bdata>> _items) : items(_items) {};
		vector<shared_ptr<bdata>> value() const { return items; }

		string display_type();
		
		friend ostream& operator<<(ostream& os, const blist &bl);
	};
}