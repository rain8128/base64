#ifndef BASE64_H
#define BASE64_H

#include <stdint.h>

int base64Encode(const uint8_t *src, size_t srclen, char *dst, size_t dstlen);

#endif /*BASE64_H*/