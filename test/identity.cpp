#define BOOST_TEST_MODULE Identity
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "bencode/bencode.h"


using namespace bencode;
using namespace boost::outcome_v2;

BOOST_AUTO_TEST_CASE(bint_identity)
{
  std::string s = "i456e";
  stringstream ss(s);
  auto dec = decode<bint>(ss);
  auto enc = encode<bint>(dec.value());
  BOOST_TEST(enc == s);
}

BOOST_AUTO_TEST_CASE(bstring_identity)
{
  std::string s = "4:aspq";
  stringstream ss(s);
  auto dec = decode<bstring>(ss);
  auto enc = encode<bstring>(dec.value());
  BOOST_TEST(enc == s);
}

BOOST_AUTO_TEST_CASE(blist_identity)
{
  std::string s = "l5:poiuyi9872ee";
  stringstream ss(s);
  auto dec = decode<blist>(ss);
  auto enc = encode<blist>(dec.value());
  BOOST_TEST(enc == s);
}

BOOST_AUTO_TEST_CASE(bdict_identity)
{
  std::string s = "d2:uili321ei765eee";
  stringstream ss(s);
  auto dec = decode<bdict>(ss);
  auto enc = encode<bdict>(dec.value());
  BOOST_TEST(enc == s);
}