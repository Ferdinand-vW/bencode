#pragma once

#include "btypes.h"
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

namespace bencode {

	class bstring {
		vector<char> m_bytes;
	public:
		bstring(std::vector<char> &&bytes) : m_bytes(std::move(bytes)) {};
		bstring(std::vector<char> &bytes) : m_bytes(bytes) {};
		
		bstring(const std::string &s) {
			m_bytes.reserve(s.size());
			std::copy(s.begin(),s.end(),back_inserter(m_bytes));
		}

		std::string display_type() const;
		const std::vector<char>& value() const { return m_bytes; }
		std::vector<char> value() { return m_bytes; }
		std::string to_string() const { return std::string(m_bytes.begin(),m_bytes.end()); }

		friend std::ostream& operator<<(std::ostream& os, const bstring& bs);
		friend bool operator<(const bstring &b1,const bstring &b2);
	};
}
