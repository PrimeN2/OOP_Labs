#include <gtest/gtest.h>
#include "Eleven.hpp"
#include <stdexcept>
#include <string>

TEST(ElevenTest, ConstructorAndToString) {
    Eleven num("A0A1");
    EXPECT_EQ(num.toString(), "A0A1");
    EXPECT_EQ(num.getSize(), 4);
}

TEST(ElevenTest, Addition) {
    Eleven a("123");
    Eleven b("45");
    Eleven result = a.add(b);
    EXPECT_EQ(result.toString(), "168");
}

TEST(ElevenTest, Subtraction) {
    Eleven a("321");
    Eleven b("123");
    Eleven result = a.subtract(b);
    EXPECT_EQ(result.toString(), "1A9");
}

TEST(ElevenTest, SubtractionThrowsIfNegative) {
    Eleven a("123");
    Eleven b("321");
    EXPECT_THROW(a.subtract(b), std::invalid_argument);
}

TEST(ElevenTest, Comparison) {
    Eleven a("123");
    Eleven b("45");
    Eleven c("123");

    EXPECT_TRUE(a.greaterThan(b));
    EXPECT_TRUE(b.lessThan(a));
    EXPECT_TRUE(a.equalTo(c));
    EXPECT_FALSE(a.equalTo(b));
}

TEST(ElevenTest, CopyAndMove) {
    Eleven original("12A");
    std::string original_str = original.toString();

    Eleven copied = original.copy();
    EXPECT_EQ(copied.toString(), original_str);

    Eleven moved = std::move(original);
    EXPECT_EQ(moved.toString(), original_str);
    EXPECT_EQ(original.toString(), "0");
}

TEST(ElevenTest, InvalidSubtraction) {
    Eleven larger{1, 0}; 
    Eleven smaller{2, 0}; 
    EXPECT_THROW(larger.subtract(smaller), std::invalid_argument);
}