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
#include <stdio.h>
#include <string.h>

class TOTPTokenGenerator {
public:
    TOTPTokenGenerator(uint8_t *key, size_t len): keylen_(len) {
        key_ = new uint8_t[len];
        memcpy(key_, key, len);
    }; 
    virtual ~TOTPTokenGenerator(){
        delete[] key_;
    }
    bool init();
    uint32_t getToken();
private:
    uint8_t *key_;
    int keylen_ = 0;
    const uint64_t   STEP_IN_SECONDS = 30L; // step in seconds
};

#endif // __TOTP_H__

