#include "bencode/bdata.h"
#include "bencode/blist.h"
#include "bencode/bint.h"
#include "bencode/bdict.h"
#include "bencode/bstring.h"
#include "bencode/utils.h"
#include <memory>

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

    shared_ptr<bdata> bdict::at(const string &s) {
        bstring bs(s);
        return kvs.at(s);
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