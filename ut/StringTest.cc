#include "String.hh"
#include <gtest/gtest.h>

TEST(StringTest, SSOShortString) {
    String s("hello");
    EXPECT_STREQ(s.get(), "hello");
}

TEST(StringTest, LongString) {
    String s("this string is definitely longer than fifteen");
    EXPECT_STREQ(s.get(), "this string is definitely longer than fifteen");
}

TEST(StringTest, CopyConstructor) {
    String s1("short");
    String s2 = s1;
    EXPECT_STREQ(s2.get(), "short");

    String s3("a really long string for testing copy constructor");
    String s4 = s3;
    EXPECT_STREQ(s4.get(), "a really long string for testing copy constructor");
}

TEST(StringTest, AssignmentOperator) {
    String s1("short");
    String s2;
    s2 = s1;
    EXPECT_STREQ(s2.get(), "short");

    String s3("a long string to test assignment operator");
    String s4;
    s4 = s3;
    EXPECT_STREQ(s4.get(), "a long string to test assignment operator");
}
