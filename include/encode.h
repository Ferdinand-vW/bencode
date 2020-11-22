#pragma  once

#include <string>

namespace bencode {
    template <class T>
    std::string encode(T t);
}