#pragma once

#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "btypes.h"
// #include "binterface.h"

using namespace std;

namespace bencode
{
	class bdict {
		map<bstring, bdata> kvs;
	public:
		bdict(map<bstring, bdata> kv) : kvs(kv) {};

		map<bstring, bdata> key_values() const {
			return kvs;
		}
		vector<bdata> values() const;
		vector<bstring> keys() const;
		string display_type() const;
		bdata at(const string &s) const;
		optional<bdata> find(const string &s) const;
		void merge(const bdict &bd);
		void insert(std::pair<bstring, bdata> kv);

		friend ostream& operator<<(ostream&, const bdict&);
	};
}