#include <stdint.h>

int validate_base32(const char *base32);
uint32_t totp_getToken(const char *base32);
