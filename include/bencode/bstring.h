#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

#include "bencode/btypes.h"

namespace bencode {

	class bstring {
		std::vector<char> m_bytes;
	public:
		bstring(const std::vector<char> &bytes) : m_bytes(bytes) {};
		
		bstring(const std::string &s) : m_bytes(s.begin(), s.end()) {}

		std::string display_type() const;
		std::vector<char> value() const { return m_bytes; }
		std::string to_string() const { return std::string(m_bytes.begin(),m_bytes.end()); }

		friend std::ostream& operator<<(std::ostream& os, const bstring& bs);
		friend bool operator<(const bstring &b1,const bstring &b2);
	};
}
