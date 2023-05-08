#include "bencode/bencode.h"
#include "gtest/gtest.h"


using namespace bencode;
// using namespace boost::outcome_v2;

TEST(identity, bint)
{
  std::string s = "i456e";
  std::stringstream ss(s);
  auto dec = decode<bint>(ss);
  auto enc = encode<bint>(dec.value());

  ASSERT_EQ(enc, s);
}

TEST(identity, bstring)
{
  std::string s = "4:aspq";
  std::stringstream ss(s);
  auto dec = decode<bstring>(ss);
  auto enc = encode<bstring>(dec.value());
  ASSERT_EQ(enc, s);
}

TEST(identity, blist)
{
  std::string s = "l5:poiuyi9872ee";
  std::stringstream ss(s);
  auto dec = decode<blist>(ss);
  auto enc = encode<blist>(dec.value());
  ASSERT_EQ(enc, s);
}

TEST(identity, bdict)
{
  std::string s = "d2:uili321ei765eee";
  std::stringstream ss(s);
  auto dec = decode<bdict>(ss);
  auto enc = encode<bdict>(dec.value());
  ASSERT_EQ(enc, s);
}
