#pragma once

#include <variant>
using namespace std;

namespace bencode {
    class bint;
    class bstring;
    class blist;
    class bdict;
    typedef variant<bint,bstring,blist,bdict> bdata;
}