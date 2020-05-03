/*
Project: TotpCommonCrypto
File: src/Base32Decoder.h

This implementation is one of base32 decoding for RFC4648.
https://tools.ietf.org/html/rfc4648 

Copyright 2020 Tomoo Mizukami <we_love_blog@yahoo.com>
Released under the MIT license
*/
#ifndef __BASE32DECODER_H__
#define __BASE32DECODER_H__

#include <string>

class Base32Decoder {
public:
    Base32Decoder(char *inputStr):input_str_(inputStr){}
    virtual ~Base32Decoder() {};
    int length() const;
    void decode(uint8_t *data, size_t keylen);
private:
    std::string input_str_;
};

#endif //__BASE32DECODER_H__
