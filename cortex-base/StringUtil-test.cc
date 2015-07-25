// This file is part of the "libcortex" project
//   (c) 2009-2015 Christian Parpart <https://github.com/christianparpart>
//   (c) 2014-2015 Paul Asmuth <https://github.com/paulasmuth>
//
// libcortex is free software: you can redistribute it and/or modify it under
// the terms of the GNU Affero General Public License v3.0.
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <cortex-base/StringUtil.h>
#include <gtest/gtest.h>

using namespace cortex;

TEST(StringUtil, toString) {
  EXPECT_EQ(StringUtil::toString(123), "123");
  EXPECT_EQ(StringUtil::toString(1230000000), "1230000000");
  EXPECT_EQ(StringUtil::toString(24.5), "24.5");
  EXPECT_EQ(StringUtil::toString("abc"), "abc");
  EXPECT_EQ(StringUtil::toString(std::string("abc")), "abc");
}

TEST(StringUtil, StripTrailingSlashes) {
  std::string s1 = "fnord/bar/";
  StringUtil::stripTrailingSlashes(&s1);
  EXPECT_EQ(s1, "fnord/bar");

  std::string s2 = "fnord/bar///";
  StringUtil::stripTrailingSlashes(&s2);
  EXPECT_EQ(s2, "fnord/bar");

  std::string s3 = "fnord/bar";
  StringUtil::stripTrailingSlashes(&s3);
  EXPECT_EQ(s3, "fnord/bar");

  std::string s4 = "/";
  StringUtil::stripTrailingSlashes(&s4);
  EXPECT_EQ(s4, "");
}

TEST(StringUtil, TestBeginsWith) {
  EXPECT_TRUE(StringUtil::beginsWith("fnord", "fn"));
  EXPECT_TRUE(StringUtil::beginsWith("fnahrad", "fn"));
  EXPECT_FALSE(StringUtil::beginsWith("ford", "fn"));
  EXPECT_TRUE(StringUtil::beginsWith("fnord", "fnord"));
  EXPECT_FALSE(StringUtil::beginsWith("fnord", "fnordbar"));
}

TEST(StringUtil, TestEndsWith) {
  EXPECT_TRUE(StringUtil::endsWith("fnord", "ord"));
  EXPECT_TRUE(StringUtil::endsWith("ford", "ord"));
  EXPECT_FALSE(StringUtil::endsWith("ford", "x"));
  EXPECT_FALSE(StringUtil::endsWith("ford", "fnord"));
  EXPECT_TRUE(StringUtil::endsWith("fnord", "fnord"));
  EXPECT_FALSE(StringUtil::endsWith("fnord", "fnordbar"));
}

TEST(StringUtil, replaceAll) {
  std::string str =
      "cloud computing, or in simpler shorthand just >the cloud<...";

  StringUtil::replaceAll(&str, "cloud", "butt");
  EXPECT_EQ(str, "butt computing, or in simpler shorthand just >the butt<...");

  StringUtil::replaceAll(&str, "butt", "");
  EXPECT_EQ(str, " computing, or in simpler shorthand just >the <...");
}

TEST(StringUtil, format) {
  auto str1 = StringUtil::format(
      "The quick $0 fox jumps over the $1 dog",
      "brown",
      "lazy");

  EXPECT_EQ(str1, "The quick brown fox jumps over the lazy dog");

  auto str2 = StringUtil::format(
      "1 $3 2 $2 3 $1 4 $0 5 $8 6 $9",
      "A",
      "B",
      "C",
      "D",
      "E",
      "F",
      "G",
      "H",
      "I",
      "K");

  EXPECT_EQ(str2, "1 D 2 C 3 B 4 A 5 I 6 K");

  auto str3 = StringUtil::format("$0 + $1 = $2", 2.5, 6.5, 9);
  EXPECT_EQ(str3, "2.5 + 6.5 = 9");

  auto str4 = StringUtil::format("$1$1$1$1$1 $0", "Batman", "Na");
  EXPECT_EQ(str4, "NaNaNaNaNa Batman");
}

TEST(StringUtil, TestSplit) {
  auto parts1 = StringUtil::split("one,two,three", ",");
  EXPECT_EQ(parts1.size(), 3);
  EXPECT_EQ(parts1[0], "one");
  EXPECT_EQ(parts1[1], "two");
  EXPECT_EQ(parts1[2], "three");

  auto parts2 = StringUtil::split("onexxtwoxxthree", "xx");
  EXPECT_EQ(parts2.size(), 3);
  EXPECT_EQ(parts2[0], "one");
  EXPECT_EQ(parts2[1], "two");
  EXPECT_EQ(parts2[2], "three");
}
