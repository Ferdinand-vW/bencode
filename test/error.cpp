#define BOOST_TEST_MODULE Error
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "bencode/bencode.h"

using namespace bencode;

BOOST_AUTO_TEST_CASE(bint_error1)
{
  std::string s = "i56s4e";
  std::stringstream ss(s);
  auto dec = decode<bint>(ss);
  BOOST_TEST(BErrorF::conversion_to_int("56s4").message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(bint_error2)
{
  std::string s = "s556";
  std::stringstream ss(s);
  auto dec = decode<bint>(ss);
  BOOST_TEST(BErrorF::expected_int_open('s').message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(bint_error3)
{
  std::string s = "i564";
  std::stringstream ss(s);
  auto dec = decode<bint>(ss);
  BOOST_TEST(BErrorF::expected_int_end().message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(bstring_error1)
{
  std::stringstream ss("3:t");
  auto dec = decode<bstring>(ss);
  BOOST_TEST(BErrorF::expected_string_symbols("t",2).message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(bstring_error2)
{
  std::stringstream ss("4");
  auto dec = decode<bstring>(ss);
  BOOST_TEST(BErrorF::expected_string_delimiter("").message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(bstring_error3)
{
  std::stringstream ss("4r:tyu");
  auto dec = decode<bstring>(ss);
  BOOST_TEST(BErrorF::expected_string_delimiter("r").message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(blist_error1)
{
  std::string s = "5:rwersei567e";
  std::stringstream ss(s);
  auto dec = decode<blist>(ss);
  BOOST_TEST(BErrorF::expected_list_open('5').message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(blist_error2)
{
  std::string s = "li564e";
  std::stringstream ss(s);
  auto dec = decode<blist>(ss);
  BOOST_TEST(BErrorF::expected_list_end().message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(bdict_error1)
{
  std::string s = "di456e3:erte";
  std::stringstream ss(s);
  auto dec = decode<bdict>(ss);
  BOOST_TEST(BErrorF::expected_string_open("i").message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(bdict_error2)
{
  std::string s = "i456e3:erte";
  std::stringstream ss(s);
  auto dec = decode<bdict>(ss);
  BOOST_TEST(BErrorF::expected_dict_open('i').message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(bdict_error3)
{
  std::string s = "d3:ert";
  std::stringstream ss(s);
  auto dec = decode<bdict>(ss);
  BOOST_TEST(BErrorF::invalid_input("").message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(bdict_error4)
{
  std::string s = "d3:erti456e";
  std::stringstream ss(s);
  auto dec = decode<bdict>(ss);
  BOOST_TEST(BErrorF::expected_dict_end().message() == dec.error().message());
}