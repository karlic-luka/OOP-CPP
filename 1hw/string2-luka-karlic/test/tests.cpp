#include "gtest/gtest.h"
#include <string> 
#include "../include/strutils.h"
 
using namespace std;

TEST(strutils, TestUpper) {
    std::string str{"abcdeTZU098"};
    auto newstr = to_upper(str);
    ASSERT_STREQ(newstr.c_str(), "ABCDETZU098");
}

TEST(strutils, TestLower) {
    std::string str{"ABCDETZU098"};
    auto newstr = to_lower(str);
    ASSERT_STREQ(newstr.c_str(), "abcdetzu098");
}

TEST(strutils, TestReverse) {
    std::string str{"ABCDETZU098"};
    auto newstr = reverse(str);
    ASSERT_STREQ(newstr.c_str(), "890UZTEDCBA");
}

TEST(strutils, TestTrimLeft) {
    std::string str{"   ABCDETZU098"};
    auto newstr = trim_left(str);
    ASSERT_STREQ(newstr.c_str(), "ABCDETZU098");

    str = "     ";
    newstr = trim_left(str);
    ASSERT_STREQ(newstr.c_str(), "");
}

TEST(strutils, TestTrimRight) {
    std::string str{"ABCDETZU098      "};
    auto newstr = trim_right(str);
    ASSERT_STREQ(newstr.c_str(), "ABCDETZU098");

    str = "     ";
    newstr = trim_right(str);
    ASSERT_STREQ(newstr.c_str(), "");
}

TEST(strutils, TestTrim) {
    std::string str{"      ABCDETZU098      "};
    auto newstr = trim(str);
    ASSERT_STREQ(newstr.c_str(), "ABCDETZU098");

    str = "     ";
    newstr = trim(str);
    ASSERT_STREQ(newstr.c_str(), "");
}

TEST(strutils, TestRemove) {
    std::string str{"ABCDET8ZU098"};
    auto newstr = remove(str, 'A');
    ASSERT_STREQ(newstr.c_str(), "BCDET8ZU098");
 
    newstr = remove(newstr, '8');
    ASSERT_STREQ(newstr.c_str(), "BCDETZU09");
}