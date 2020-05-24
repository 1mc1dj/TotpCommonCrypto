/*
Project: TotpCommonCrypto
File: src/Base32Decoder.cpp

This implementation is one of base32 decoding for RFC4648.
https://tools.ietf.org/html/rfc4648 

Copyright 2020 Tomoo Mizukami <we_love_blog@yahoo.com>
Released under the MIT license
*/
#include <string>
#include <vector>
#include "Base32Decoder.h"
#include "ByteSwap.h"
#include <iostream>

int Base32Decoder::length() const{
    // check Range of values
    if (!std::all_of(input_str_.begin(), input_str_.end(), [](char c)->bool {
        return (((c > 0x31) && (c<0x38)) || ((c>0x40) && (c<0x5b)) || (c==0x3d));
    } ) ) {
        return -1;
    }

    // find first position of Padding
    std::size_t found = input_str_.find(std::string("="));
    if (found == std::string::npos) {
        if (input_str_.length() * 5 % 8 == 0) {
            return (int)(input_str_.length() * 5)/8;
        } else {
            return ((int)(input_str_.length() * 5)/8) + 1;
        }
    }
    int ret = (int)(found) * 5 / 8;
    return (found * 5 % 8 == 0) ? ret: ret;
}

void Base32Decoder::decode(uint8_t *data, size_t keylen){
    std::vector<uint8_t> base32digitVector;
    for (char c : input_str_) {
        if ((c > 0x31) && (c<0x38)) {
            base32digitVector.push_back((c - 0x32 + 26));
        }
        if ((c>0x40) && (c<0x5b)) {
            base32digitVector.push_back((c - 0x41));
        }
    }

    std::vector<uint64_t> fortyBitValueVector;
    bool bExistPadding = base32digitVector.size() % 8 == 0;
    int fortyBitValueVector_length = bExistPadding ? (int)(base32digitVector.size()/8) : (int)(base32digitVector.size()/8) +1;
    for (int i = 0; i < fortyBitValueVector_length; i++) {
        uint64_t bin = 0;
        if (i != bExistPadding ? fortyBitValueVector_length : fortyBitValueVector_length-1) {
            for (int j = 0; j < 8; j++) {
                bin |= ((uint64_t)base32digitVector[i*8+j]) << ((7-j)*5);
            }
            fortyBitValueVector.push_back(bin);         
        }  else {
            for (int j = 0; j < base32digitVector.size()%8; j++) {
                bin |= ((uint64_t)base32digitVector[i*8+j]) << ((7-j)*5);
            }
            fortyBitValueVector.push_back(bin);         
        }
    }

    int i = 0;

    uint8_t *temp_buf = new uint8_t[fortyBitValueVector.size()*5];
    for (auto it = fortyBitValueVector.begin();it != fortyBitValueVector.end(); it++ ) {
        uint64_t bs_t_val = bswap_64(*it) >> 24;
        memcpy( &temp_buf[i*5], &bs_t_val, 5);
        i++;
    }
    memcpy(data, temp_buf, keylen);
    delete[] temp_buf;
}
