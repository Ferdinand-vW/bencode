#define BOOST_TEST_MODULE Empty
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "encode.h"
#include "decode.h"
#include "btypes.h"
#include "error.h"

using namespace bencode;

BOOST_AUTO_TEST_CASE(bint_empty)
{
  stringstream ss("ie");
  auto dec = decode<bint>(ss);
  BOOST_TEST(BErrorF::conversion_to_int("").message() == dec.error().message());
}

BOOST_AUTO_TEST_CASE(bstring_empty)
{
  stringstream ss("0:");
  auto dec = decode<bstring>(ss);
  auto enc = encode(dec.value());
  BOOST_TEST(enc == "0:");
}

BOOST_AUTO_TEST_CASE(blist_empty)
{
  stringstream ss("le");
  auto dec = decode<blist>(ss);
  auto enc = encode(dec.value());
  BOOST_TEST(enc == "le");
}

BOOST_AUTO_TEST_CASE(bdict_empty)
{
  stringstream ss("de");
  auto dec = decode<bdict>(ss);
  auto enc = encode(dec.value());
  BOOST_TEST(enc == "de");
}