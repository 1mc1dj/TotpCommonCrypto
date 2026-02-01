#ifndef C_HEADER_H_
#define C_HEADER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int validate_base32(const char *base32);
uint32_t totp_getToken(const char *base32);

#ifdef __cplusplus
}
#endif

#endif // C_HEADER_H_
