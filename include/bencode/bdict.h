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
		map<bstring, bdata> m_kvs;
	public:
		bdict(map<bstring, bdata> &&kv) : m_kvs(std::move(kv)) {};
		bdict(map<bstring, bdata> &kv)  : m_kvs(kv) {};

		const map<bstring, bdata>& key_values() const {
			return m_kvs;
		}
		std::vector<bdata> values() const;
		std::vector<bstring> keys() const;
		std::string display_type() const;
		const bdata& at(const string &s) const;
		const std::optional<bdata> find(const string &s) const;
		void merge(const bdict &bd);
		void insert(std::pair<bstring, bdata> kv);

		friend std::ostream& operator<<(std::ostream&, const bdict&);
	};
}