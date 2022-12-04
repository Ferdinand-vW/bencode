#pragma once

#include <variant>
#include <memory>

#include <boost/outcome/outcome.hpp>
#include "error.h"

using namespace boost::outcome_v2;

namespace bencode {
    class bint;
    class bstring;
    class blist;
    class bdict;
    class bdata;
    typedef std::variant<bint,bstring,blist,bdict> bencoding;

    template<class T,class E = BError>
    using either = checked<T,E>;
}