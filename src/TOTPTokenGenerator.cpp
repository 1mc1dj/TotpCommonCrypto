/*
Project: TotpCommonCrypto
File: src/TOTPTokenGenerator.cpp

This is one of implementation of TOTP(Time-Based One-Time Password 
Algorithm:RFC6258).
https://tools.ietf.org/html/rfc6238

This software uses HMAC-SHA1 of CommonCrypto Library
(System Framework) for macOS/iOS.

Copyright 2020 Tomoo Mizukami <we_love_blog@yahoo.com>
Released under the MIT license
*/
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <CommonCrypto/CommonHMAC.h>
#include "TOTPTokenGenerator.h"
#include "ByteSwap.h"

TOTPTokenGenerator::TOTPTokenGenerator(uint8_t *sec, size_t keylen)
:key_str_((char *)sec), keylen_(keylen) 
{}

uint32_t TOTPTokenGenerator::getToken(){
    uint64_t t = time(NULL)  / STEP_IN_SECONDS; // get time
    t = bswap_64(t); // time_t to big endian
    uint8_t    cchmac_result[64] = {};
    
    // execute SHA1-HMAC with CommonCrypto Library
    CCHmac(kCCHmacAlgSHA1, (void *)key_str_.c_str(), keylen_, (void *)&t, sizeof(t), (void *)cchmac_result);

    // truncates hash
    uint64_t offset   = cchmac_result[19] & 0x0f;
    uint32_t binary = (cchmac_result[offset]  & 0x7f) << 24 | (cchmac_result[offset+1] & 0xff) << 16 | (cchmac_result[offset+2] & 0xff) <<  8 | (cchmac_result[offset+3] & 0xff) ;

    // truncates to 6 digits
    uint32_t digits = binary % 1000000;
    return digits;
}
