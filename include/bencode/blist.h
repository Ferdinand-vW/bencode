#pragma once

#include <ostream>
#include <vector>
#include "btypes.h"

using namespace std;

namespace bencode {
	class blist {
		vector<shared_ptr<bdata>> items;

	public:
		blist(vector<shared_ptr<bdata>> _items) : items(_items) {};
		vector<shared_ptr<bdata>> value() const { return items; }

		string display_type();
		void traverse(function<void(bencoding_prim)> f);

		friend ostream& operator<<(ostream& os, const blist &bl);
	};
}