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
		map<bstring, shared_ptr<bdata>> kvs;
	public:
		bdict(map<bstring, shared_ptr<bdata>> kv) : kvs(kv) {};

		map<bstring, shared_ptr<bdata>> key_values() const {
			return kvs;
		}
		vector<shared_ptr<bdata>> values() const;
		vector<bstring> keys() const;
		string display_type() const;
		shared_ptr<bdata> at(const string &s);

		friend ostream& operator<<(ostream&, const bdict&);
	};
}