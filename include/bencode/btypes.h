#pragma once

#include <boost/outcome/basic_outcome.hpp>
#include <boost/outcome/basic_result.hpp>
#include <boost/outcome/std_result.hpp>
#include <variant>
#include <memory>

#include <boost/outcome/outcome.hpp>
#include "error.h"

using namespace std;
using namespace boost::outcome_v2;

namespace bencode {
    class bint;
    class bstring;
    class blist;
    class bdict;
    class bdata;
    typedef variant<bint,bstring,blist,bdict> bencoding;
    typedef variant<bint,bstring,bdata,pair<bstring,bdata>> flat_bencoding;

    template<class T,class E = BError>
    using either = checked<T,E>;
}