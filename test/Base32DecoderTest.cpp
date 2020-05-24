
#include "gtest/gtest.h"
#include "Base32Decoder.h"
#include <stdio.h>
#include <string.h>
#include <random>
#include <algorithm>
#include <string>

TEST(Base32DecorderTest, alloc) {
    std::unique_ptr<Base32Decoder> b32(new Base32Decoder("abcde"));
    EXPECT_TRUE(b32 != nullptr);
}

TEST(Base32DecorderTest, length01) {
    std::unique_ptr<Base32Decoder> b32(new Base32Decoder("abcde"));
    EXPECT_TRUE( b32->length() ==  -1);
}

std::string random_base32_test(int length) {
    std::string text;
    generate_n(text.begin(), length, []() -> char {
        std::random_device rnd;
        std::mt19937 mt(rnd());
        char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
        char result = char_set[mt() % 32];
        return result;
    });
 
    return text;
}

TEST(Base32DecorderTest, length02) {
    for (int i=0; i < 100; i++) {
        std::unique_ptr<Base32Decoder> b32(new Base32Decoder((char *)random_base32_test(8).c_str()));
        EXPECT_TRUE( b32->length() ==  5);
    }
}

TEST(Base32DecorderTest, length_zero) {
    char input_cstring[41] = {};
    std::unique_ptr<Base32Decoder> b32(new Base32Decoder(input_cstring));
    EXPECT_TRUE( b32->length() ==  0);
}

TEST(Base32DecorderTest, length_minus_1) {
    std::unique_ptr<Base32Decoder> b32(new Base32Decoder("ABcDE"));
    EXPECT_TRUE( b32->length() ==  -1);
}

TEST(Base32DecorderTest, include_equal) {
    std::unique_ptr<Base32Decoder> b32(new Base32Decoder("NVUQ="));
    ASSERT_EQ( b32->length(),2);
}


#define TEST_BUF_BASE32_DECODETEST(X,Y)     TEST(Base32DecorderTest, X) { \
    std::unique_ptr<Base32Decoder> b32(new Base32Decoder((char *)testData[Y].inputBase32)); \
    ASSERT_EQ( b32->length(),testData[Y].len); \
    char *buf = new char[testData[Y].len + 1]; \
    memset(buf, 0, testData[Y].len + 1); \
    b32->decode((uint8_t *)buf,b32->length()); \
    ASSERT_STREQ(testData[Y].outputBase32, buf); \
    delete[] buf; \
} 

#include "Base32randomStr.inc"