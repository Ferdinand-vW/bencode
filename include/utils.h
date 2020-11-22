#pragma once

#include <new>
#include <variant>
#include <functional>
#include "iostream"
#include "btypes.h"
#include "bdict.h"
#include "blist.h"
#include "bint.h"
#include "bstring.h"

using namespace std;

namespace bencode {

	template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
	template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;	
}