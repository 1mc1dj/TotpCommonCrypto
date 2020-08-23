#include <stdio.h>
#include "base32_decoder.h"
#include "totp_token_generator.h"

extern "C" int validate_base32(const char *base32);
extern "C" uint32_t totp_getToken(const char *base32);

int validate_base32(const char *base32) {
    Base32Decoder b3d((char *)base32);
    int keylen = b3d.length();
    if (keylen < 0) {
        fprintf(stderr, "Error: Invalid domain secret(%s)\n", base32);
        return -1;
    }
    return 0;
}

uint32_t totp_getToken(const char *base32) {
    Base32Decoder b3d((char *)base32);
    int keylen = b3d.length();
    if (keylen < 0) {
        fprintf(stderr, "Error: Invalid domain secret(%s)\n", base32);
        return -1;
    }
    uint8_t data[keylen];
    b3d.decode(data, keylen);

    // get time token
    TOTPTokenGenerator tg(data, keylen);
    return tg.getToken();
}

