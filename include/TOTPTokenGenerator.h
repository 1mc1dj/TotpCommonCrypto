/*
Project: TotpCommonCrypto
File: src/TOTPTokenGenerator.h

This is one of implementation of TOTP(Time-Based One-Time Password 
Algorithm:RFC6258).
https://tools.ietf.org/html/rfc6238

This software uses HMAC-SHA1 of CommonCrypto Library
(System Framework) for macOS/iOS.

Copyright 2020 Tomoo Mizukami <we_love_blog@yahoo.com>
Released under the MIT license
*/
#ifndef __TOTP_H__
#define __TOTP_H__

#include <string>

class TOTPTokenGenerator {
public:
    TOTPTokenGenerator(uint8_t *key, size_t len);
    virtual ~TOTPTokenGenerator(){}
    bool init();
    uint32_t getToken();
private:
    std::string key_str_;
    int keylen_ = 0;
    const uint64_t   STEP_IN_SECONDS = 30L; // step in seconds
};

#endif // __TOTP_H__

