#include "bencode/bdata.h"
#include "bencode/blist.h"
#include "bencode/bint.h"
#include "bencode/bdict.h"
#include "bencode/bstring.h"
#include "bencode/utils.h"
#include <memory>
#include <optional>

namespace bencode {

    std::string bdict::display_type() const {
        return "bdict";
    }

    std::vector<bstring> bdict::keys() const {
        std::vector<bstring> vec;
        for(auto &kvp : m_kvs) {
            vec.push_back(kvp.first);
        }
        return vec;
	}
    
    const bdata& bdict::at(const std::string &s) const {
        bstring bs(std::vector<char>(s.begin(),s.end()));
        return m_kvs.at(bs);
    }

    const bdata* bdict::find(const std::string &s) const {
        bstring bs(std::vector<char>(s.begin(),s.end()));
        auto v_it = m_kvs.find(bs);
        if(v_it != m_kvs.end()) {
            return &v_it->second;
        } else {
            return nullptr;
        }
    }

    void bdict::merge(const bdict &bd) {
        auto keyvals = bd.key_values();
		m_kvs.merge(keyvals);
	}

	void bdict::insert(const bstring& bs, const bdata& bd) {
        m_kvs.emplace(bs, bd);
    }

    std::ostream& operator<<(std::ostream& os, const bdict &bd) {
        auto m_kvs = bd.key_values();
        os << "{";

        bool first = true;
        for (const auto& kv : m_kvs) {
            
            if (first) { first = false; }
            else { os << ", "; } // add comma between items

            os << kv.first.to_string() + " => ";
            os << kv.second;
        }

        os << "}";

        return os;
	}
}