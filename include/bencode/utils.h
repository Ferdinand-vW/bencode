#pragma once

#include <new>
#include <variant>
#include <functional>
#include "iostream"

namespace bencode {

	template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
	template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
}