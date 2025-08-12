#include "t2_parser.h"
#include <gtest/gtest.h>

TEST(T2ParserTest, Empty) {
    auto input  = R""""( )"""";
    auto parser = new T2Parser();
    auto result = parser->parse(input);
    EXPECT_EQ(result, nullptr);
}

TEST(T2ParserTest, RootNoBraces) {
    auto input =
        R""""(
        root
)"""";
    auto parser = new T2Parser();
    auto result = parser->parse(input);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result->value.c_str(), "root");
    EXPECT_EQ(result->left, nullptr);
    EXPECT_EQ(result->right, nullptr);
}

TEST(T2ParserTest, RootOnlyOpenBrace) {
    auto input =
        R""""(
        root {
)"""";
    auto parser = new T2Parser();
    auto result = parser->parse(input);
    EXPECT_EQ(result, nullptr);
}

TEST(T2ParserTest, RootOnly) {
    auto input =
        R""""(
root12 {
}
)"""";
    auto parser = new T2Parser();
    auto result = parser->parse(input);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result->value.c_str(), "root12");
    EXPECT_EQ(result->left, nullptr);
    EXPECT_EQ(result->right, nullptr);
}
TEST(T2ParserTest, WithChildren) {
    auto input =
        R""""(
root {
    < left23
    > right {
        < 12
        > 13
    }
}
)"""";
    auto parser = new T2Parser();
    auto result = parser->parse(input);
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result->value.c_str(), "root");
    EXPECT_NE(result->left, nullptr);
    EXPECT_NE(result->right, nullptr);
    EXPECT_NE(result->right->left, nullptr);
    EXPECT_NE(result->right->right, nullptr);
    EXPECT_STREQ(result->left->value.c_str(), "left23");
    EXPECT_STREQ(result->right->value.c_str(), "right");
    EXPECT_STREQ(result->right->left->value.c_str(), "12");
    EXPECT_STREQ(result->right->right->value.c_str(), "13");
}
