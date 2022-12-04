#define BOOST_TEST_MODULE Bsort
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "bencode/bencode.h"

using namespace bencode;

BOOST_AUTO_TEST_CASE(bdict_is_sorted)
{
  std::string s = "d3:abci1e1:ci0ee";
  std::stringstream ss(s);
  auto dec = decode<bdict>(ss);
  auto enc = encode<bdict>(dec.value());
  BOOST_TEST(enc == s);
}

BOOST_AUTO_TEST_CASE(bdict_is_reverted)
{
  std::string s = "d3:cefi0e1:ai1ee";
  std::string exp = "d1:ai1e3:cefi0ee";
  std::stringstream ss(s);
  auto dec = decode<bdict>(ss);
  auto enc = encode<bdict>(dec.value());
  BOOST_TEST(enc == exp);
}

BOOST_AUTO_TEST_CASE(bdict_same_init)
{
  std::string s = "d1:bi1e1:ai1ee";
  std::string exp = "d1:ai1e1:bi1ee";
  std::stringstream ss(s);
  auto dec = decode<bdict>(ss);
  auto enc = encode<bdict>(dec.value());
  BOOST_TEST(enc == exp);
}