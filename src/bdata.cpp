#include "bdata.h"


namespace bencode {
    ostream& operator<<(ostream &os,const bdata &bd) {
		auto benc = bd.get_internal();
		std:visit([&os](auto &v) { os << v;}, benc);

		return os;
	}
}