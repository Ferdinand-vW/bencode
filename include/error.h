#pragma once

#include <ostream>
#include <string>
#include <system_error>
#include <type_traits>

namespace bencode {
    class BError {
        std::string m;
        public:
            BError(std::string x = "") : m(x) {};
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

            static BError conversion_to_int(std::string s) {
                return BError("Could not convert input " + s + " to int.");
            }

            static BError expected_string_symbols(int n) {
                return BError("Found end of stream. bstring expected " + std::to_string(n) + " more symbols");
            }

            static BError generic_error(std::string m) {
                return BError(m);
            }
    };
}
