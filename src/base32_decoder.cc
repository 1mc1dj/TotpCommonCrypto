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
#include "base32_decoder.h"
#include "byte_swap.h"
#include <iostream>

int Base32Decoder::length() const {
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

void Base32Decoder::decode(uint8_t *data, size_t keylen) {

    // local variables
    std::vector<uint8_t> base32digitVector;
    std::vector<uint64_t> fortyBitValueVector;
    size_t counter = 0;

    // change word to value
    for (char c : input_str_) {
        if ((c > 0x31) && (c<0x38)) {
            base32digitVector.push_back((c - 0x32 + 26));
        }
        if ((c>0x40) && (c<0x5b)) {
            base32digitVector.push_back((c - 0x41));
        }
    }

    // prepare data per 40 bits
    size_t numOfBitCopy = base32digitVector.size();
    bool bExistPadding = numOfBitCopy % 8 == 0;
    int fortyBitValueVector_length = bExistPadding ? (int)(base32digitVector.size()/8) : (int)(base32digitVector.size()/8) +1;

    for (int i = 0; i < fortyBitValueVector_length; i++) {
        // 40 bit copy
        uint64_t bin = 0;
        for (int j = 0; j < 8; j++) {
            uint64_t valueBits = ((uint64_t)base32digitVector[i*8+j]) << ((7-j)*5);
            bin |= valueBits;
            counter += 1;
            if (numOfBitCopy == counter) {
                break;
            }
        }
        fortyBitValueVector.push_back(bin);
    }


    // copy to target per 40 bits with endian swapping
    counter = 0;
    uint8_t *temp_buf = new uint8_t[fortyBitValueVector.size()*5];
    memset(temp_buf, 0, fortyBitValueVector.size()*5);

    for (auto it = fortyBitValueVector.begin(); it != fortyBitValueVector.end(); it++ ) {
        uint64_t bs_t_val = bswap_64( *it ) >> 24;
        memcpy( &temp_buf[counter*5], &bs_t_val, 5);
        counter++;
    }
    memcpy(data, temp_buf, keylen);
    delete[] temp_buf;
}
