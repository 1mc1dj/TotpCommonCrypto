/*
Project: TotpCommonCrypto
File: include/ByteSwap.h

bytesswap.h compatible code for ios/macOS for operating endian. 

Copyright 2020 Tomoo Mizukami <we_love_blog@yahoo.com>
Released under the MIT license
*/
#ifndef __BYTESWAP_H__
#define __BYTESWAP_H__

#if HAVE_BYTESWAP_H
#include <byteswap.h>
#else
#define bswap_16(value) \
((((value) & 0xff) << 8) | ((value) >> 8))

#define bswap_32(value) \
(((uint32_t)bswap_16((uint16_t)((value) & 0xffff)) << 16) | \
(uint32_t)bswap_16((uint16_t)((value) >> 16)))

#define bswap_64(value) \
(((uint64_t)bswap_32((uint32_t)((value) & 0xffffffff)) \
<< 32) | \
(uint64_t)bswap_32((uint32_t)((value) >> 32)))
#endif

#endif //__BYTESWAP_H__
