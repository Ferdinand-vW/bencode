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
    vector<shared_ptr<bdata>> bdict::values() const {
        vector<shared_ptr<bdata>> vec;
        for(auto &kvp : kvs) {
            vec.push_back(kvp.second);
        }
        return vec;
    }

    shared_ptr<bdata> bdict::at(const string &s) const {
        bstring bs(s);
        return kvs.at(s);
    }

    optional<shared_ptr<bdata>> bdict::find(const string &s) const {
        bstring bs(s);
        auto v_it = kvs.find(s);
        if(v_it != kvs.end()) {
            return v_it->second;
        } else {
            return {};
        }
    }

    ostream& operator<<(ostream& os, const bdict &bd) {
        auto kvs = bd.key_values();
        os << "{";

        bool first = true;
        for (const auto& kv : kvs) {
            
            if (first) { first = false; }
            else { os << ", "; } // add comma between items

            os << kv.first.value() + " => ";
            os << (*kv.second);
        }

        os << "}";

        return os;
	}
}