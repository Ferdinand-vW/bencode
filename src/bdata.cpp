#include "bencode/bdata.h"


namespace bencode {
    ostream& operator<<(ostream &os,const bdata &bd) {
		auto benc = bd.value();
		std:visit([&os](auto &v) { os << v;}, benc);

		return os;
	}
}