#pragma  once

#include <string>
#include "bdata.h"
namespace bencode {
    template <class T>
    std::string encode(T t);

    template<>
    std::string encode<bdata>(bdata bd);
}