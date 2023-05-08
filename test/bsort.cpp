#include "bencode/bencode.h"
#include "gtest/gtest.h"

using namespace bencode;

TEST(bsort, bdict_is_sorted)
{
  std::string s = "d3:abci1e1:ci0ee";
  std::stringstream ss(s);
  auto dec = decode<bdict>(ss);
  auto enc = encode<bdict>(dec.value());
  ASSERT_EQ(enc, s);
}

TEST(bsort, bdict_is_reverted)
{
  std::string s = "d3:cefi0e1:ai1ee";
  std::string exp = "d1:ai1e3:cefi0ee";
  std::stringstream ss(s);
  auto dec = decode<bdict>(ss);
  auto enc = encode<bdict>(dec.value());
  ASSERT_EQ(enc, exp);
}

TEST(bsort, bdict_same_init)
{
  std::string s = "d1:bi1e1:ai1ee";
  std::string exp = "d1:ai1e1:bi1ee";
  std::stringstream ss(s);
  auto dec = decode<bdict>(ss);
  auto enc = encode<bdict>(dec.value());
  ASSERT_EQ(enc, exp);
}