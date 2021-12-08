#pragma  once

#include <string>
#include "bdata.h"
namespace bencode {
    template <class T>
    std::string encode(const T& t);

    template<>
    std::string encode<bdata>(const bdata &bd);
}