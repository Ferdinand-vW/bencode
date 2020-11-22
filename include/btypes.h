#pragma once

#include <boost/outcome/basic_outcome.hpp>
#include <boost/outcome/basic_result.hpp>
#include <boost/outcome/std_result.hpp>
#include <error.h>
#include <variant>
#include <memory>

#include <boost/outcome/outcome.hpp>

using namespace std;
using namespace boost::outcome_v2;

namespace bencode {
    class bint;
    class bstring;
    class blist;
    class bdict;
    class bdata;
    typedef variant<bint,bstring,blist,bdict> bencoding;

    template<class T,class E = BError>
    using either = checked<T,E>;
}