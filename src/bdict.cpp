#include "bencode/bdata.h"
#include "bencode/blist.h"
#include "bencode/bint.h"
#include "bencode/bdict.h"
#include "bencode/bstring.h"
#include "bencode/utils.h"
#include <memory>
#include <optional>

namespace bencode {

    string bdict::display_type() const {
        return "bdict";
    }

    vector<bstring> bdict::keys() const {
        vector<bstring> vec;
        for(auto &kvp : m_kvs) {
            vec.push_back(kvp.first);
        }
        return vec;
	}
    vector<bdata> bdict::values() const {
        vector<bdata> vec;
        for(auto &kvp : m_kvs) {
            vec.push_back(kvp.second);
        }
        return vec;
    }

    const bdata& bdict::at(const string &s) const {
        bstring bs(vector<char>(s.begin(),s.end()));
        return m_kvs.at(bs);
    }

    const std::optional<bdata> bdict::find(const string &s) const {
        bstring bs(vector<char>(s.begin(),s.end()));
        auto v_it = m_kvs.find(bs);
        if(v_it != m_kvs.end()) {
            return v_it->second;
        } else {
            return {};
        }
    }

    void bdict::merge(const bdict &bd) {
        auto keyvals = bd.key_values();
		m_kvs.merge(keyvals);
	}

	void bdict::insert(std::pair<bstring, bdata> kv) {
        m_kvs.insert(kv);
    }

    ostream& operator<<(ostream& os, const bdict &bd) {
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