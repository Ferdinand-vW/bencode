#include <system_error>
#include <type_traits>
#include <boost/system/error_code.hpp>

using namespace boost::system;

namespace bencode {
    enum class BDecodeErrc {
        expected_dict_open = 1,
        expected_dict_end  = 2,
        expected_list_open = 3,
        expected_list_end  = 4
    };
}


namespace boost
{
    namespace system {
        template <> struct is_error_code_enum<bencode::BDecodeErrc> : std::true_type {};
    }
}

namespace bencode {
    class BDecodeErrc_category : public boost::system::error_category {
        virtual const char *name() const noexcept override final { return "Bencode decode error"; }
        virtual std::string message(int c) const override final {
            switch (static_cast<BDecodeErrc>(c)) {
                case BDecodeErrc::expected_dict_open:
                    return "bdict: expected symbol 'd'";
                case BDecodeErrc::expected_dict_end:
                    return "bdict: found end of stream. bdict must be closed with 'e'";
                case BDecodeErrc::expected_list_open:
                    return "blist: expected symbol 'l'";
                case BDecodeErrc::expected_list_end:
                    return "blist: found end of stream. blist must be closed with 'e'";
                default: 
                    return "Unknown";
            }
        }

        virtual boost::system::error_condition default_error_condidition(int c) const noexcept final {
            switch(static_cast<BDecodeErrc>(c)) {
                case BDecodeErrc::expected_dict_open:
                    return make_error_condition(boost::system::errc::invalid_argument);
                case BDecodeErrc::expected_dict_end:
                    return make_error_condition(boost::system::errc::invalid_argument);
                case BDecodeErrc::expected_list_open:
                    return make_error_condition(boost::system::errc::invalid_argument);
                case BDecodeErrc::expected_list_end:
                    return make_error_condition(boost::system::errc::invalid_argument);
                default:
                    return boost::system::error_condition(c,*this);
            }
        }
    };
}

#define THIS_MODULE_API_DECL extern inline
THIS_MODULE_API_DECL const bencode::BDecodeErrc_category &BDecodeErrc_category()
{
  static bencode::BDecodeErrc_category c;
  return c;
}


// Overload the global make_error_code() free function with our
// custom enum. It will be found via ADL by the compiler if needed.
namespace bencode {
    inline boost::system::error_code make_error_code(bencode::BDecodeErrc e)
    {
    return {static_cast<int>(e), BDecodeErrc_category()};
    }
}
