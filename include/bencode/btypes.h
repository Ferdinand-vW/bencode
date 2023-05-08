#pragma once

#include <variant>
#include <memory>

#include <boost/outcome/outcome.hpp>
#include "error.h"

using namespace boost::outcome_v2;

namespace bencode {
    template<class T,class E = BError>
    using either = checked<T,E>;

}