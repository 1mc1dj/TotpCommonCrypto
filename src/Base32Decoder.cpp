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

int Base32Decoder::length() const{
    // check Range of values
    for (char c : input_str_) {
        if (((c > 0x31) && (c<0x38)) || ((c>0x40) && (c<0x5b))) {
            continue;
        } else {
            if (0x3d != c) {
                // base32 validation error
                return -1;
            }
        }
    }

    // find first position of Padding
    std::size_t found = input_str_.find(std::string("="));
    if (found == std::string::npos) {
        return (input_str_.length() * 5)/8;
    }
    return (found) * 5 / 8;
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
    int fortyBitValueVector_length = bExistPadding ? (base32digitVector.size()/8) : (base32digitVector.size()/8) +1;
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
    for (uint64_t t : fortyBitValueVector) {
        uint64_t bs_t_val = bswap_64(t) >> 24;
        if (i != fortyBitValueVector.size()%5 == 0 ? fortyBitValueVector.size() : fortyBitValueVector.size() - 1) {
            memcpy( &data[i*5], &bs_t_val, 5);        
        } else {
            memcpy( &data[i*5], &bs_t_val, keylen % 5);        
        }
        i++;
    }
}
