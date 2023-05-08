#pragma once

#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <optional>

#include "bencode/bstring.h"
#include "bencode/btypes.h"

namespace bencode
{
	struct bdata;
	class bdict {
		std::map<bstring, std::shared_ptr<bdata>> m_kvs;
	public:
		bdict(const std::map<bstring, std::shared_ptr<bdata>> &kv)  : m_kvs(kv) {};
		bdict(const std::map<bstring, bdata> &kv);

		const std::map<bstring, std::shared_ptr<bdata>>& key_values() const {
			return m_kvs;
		}
		const std::vector<bdata>& values() const;
		std::vector<bstring> keys() const;
		std::string display_type() const;
		const bdata& at(const std::string &s) const;
		const bdata* find(const std::string &s) const;
		void merge(const bdict &bd);
		void insert(const bstring& bs, const bdata& bd);

		friend std::ostream& operator<<(std::ostream&, const bdict&);
	};
}