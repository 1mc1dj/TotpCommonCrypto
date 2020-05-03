#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Base32Decoder.h"
#include "TOTPTokenGenerator.h"

int main(int ac,char **av) {
    if (ac != 2) {
        fprintf(stderr, "%s <secret>\n", av[0]);
        return -1;
    }

    // base32 decode
    Base32Decoder b3d((char *)av[1]);
    int keylen = b3d.length();
    if (keylen < 0) {
        fprintf(stderr, "Error: Invalid domain secret(%s)\n", av[1]);
        return -1;
    }
    uint8_t data[keylen];
    b3d.decode(data, keylen);

    // get time token
    TOTPTokenGenerator tg(data, keylen);
    printf("onetime pass: %06u\n", tg.getToken());
    return 0;
}

