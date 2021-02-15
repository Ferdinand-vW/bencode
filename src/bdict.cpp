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
        for(auto &kvp : kvs) {
            vec.push_back(kvp.first);
        }
        return vec;
	}
    vector<bdata> bdict::values() const {
        vector<bdata> vec;
        for(auto &kvp : kvs) {
            vec.push_back(kvp.second);
        }
        return vec;
    }

    bdata bdict::at(const string &s) const {
        bstring bs(vector<char>(s.begin(),s.end()));
        return kvs.at(bs);
    }

    optional<bdata> bdict::find(const string &s) const {
        bstring bs(vector<char>(s.begin(),s.end()));
        auto v_it = kvs.find(bs);
        if(v_it != kvs.end()) {
            return v_it->second;
        } else {
            return {};
        }
    }

    void bdict::merge(const bdict &bd) {
			kvs.merge(bd.key_values());
	}

	void bdict::insert(std::pair<bstring, bdata> kv) {
        kvs.insert(kv);
    }

    ostream& operator<<(ostream& os, const bdict &bd) {
        auto kvs = bd.key_values();
        os << "{";

        bool first = true;
        for (const auto& kv : kvs) {
            
            if (first) { first = false; }
            else { os << ", "; } // add comma between items

            os << kv.first.to_string() + " => ";
            os << kv.second;
        }

        os << "}";

        return os;
	}
}