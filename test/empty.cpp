#include "bencode/bencode.h"
#include "gtest/gtest.h"

using namespace bencode;

TEST(empty, bint_empty)
{
  std::stringstream ss("ie");
  auto dec = decode<bint>(ss);
  ASSERT_EQ(BErrorF::conversion_to_int("").message(), dec.error().message());
}

TEST(empty, bstring_empty)
{
  std::stringstream ss("0:");
  auto dec = decode<bstring>(ss);
  auto enc = encode(dec.value());
  ASSERT_EQ(enc, "0:");
}

TEST(empty, blist_empty)
{
  std::stringstream ss("le");
  auto dec = decode<blist>(ss);
  auto enc = encode(dec.value());
  ASSERT_EQ(enc, "le");
}

TEST(empty, bdict_empty)
{
  std::stringstream ss("de");
  auto dec = decode<bdict>(ss);
  auto enc = encode(dec.value());
  ASSERT_EQ(enc, "de");
}