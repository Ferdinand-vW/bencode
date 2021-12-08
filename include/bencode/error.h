#pragma once

#include <ostream>
#include <string>
#include <system_error>
#include <type_traits>

namespace bencode {
    class BError {
        std::string m;
        public:
            BError(std::string &&x = "") : m(std::move(x)) {};
            std::string message() { return "Error! " + m; }
            friend std::ostream& operator<<(std::ostream& os, BError be) {
                os << be.message();
                return os;
            }
    };

    class BErrorF {
        public:
            static BError expected_dict_open(char c) {
                return BError(std::string("Expected symbol 'd', but got ") + c);
            }

            static BError expected_dict_end() {
                return BError("Found end of stream. bdict must be closed with 'e'");
            }

            static BError expected_list_open(char c) {
                return BError(std::string("Expected symbol 'l', but got ") + c);
            }

            static BError expected_list_end() {
                return BError(std::string("Found end of stream. blist must be closed with 'e'"));
            }

            static BError expected_int_open(char c) {
                return BError(std::string("Expected symbol 'i', but got ") + c);
            }

            static BError expected_int_end() {
                return BError(std::string("Found end of stream. bint must be closed with 'e'"));
            }

            static BError conversion_to_int(const std::string &s) {
                return BError("Could not convert input " + s + " to int.");
            }

            static BError expected_string_open(const std::string &s) {
                return BError("BString must start with an integer. Found symbol " + s);
            }

            static BError expected_string_symbols(const std::string &s,int n) {
                return BError("Found end of stream. Parsed \"" + s + "\". Expecting " + std::to_string(n) + " more symbols");
            }

            static BError expected_string_delimiter(const std::string &s) {
                return BError(std::string("Expected symbol ':', but got ") + s);
            }

            static BError invalid_input(const std::string & s) {
                return BError("Invalid Input. Next symbol is " + s);
            }

            static BError generic_error(std::string &&m) {
                return BError(std::move(m));
            }
    };
}
