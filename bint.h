#pragma once

#include "btypes.h"

namespace bencode {

	class bint {
		int i;
	public:
		bint(int j) : i(j) {};

		int get_internal()  { return i; }
	};
}