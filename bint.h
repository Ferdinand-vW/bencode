#pragma once

#include "bdata.h"

namespace bencode {

	class bint {
		int i;
	public:
		bint(int j) : i(j) {};
	};
}