
Base64 encoding/decoding library in C.

# Reference

#### base64Encode 

```C
int base64Encode(const uint8_t *src, size_t srclen, char *dst, size_t dstlen);
```

Encodes the byte string `src` of length `srclen` into the null-terminated string `dst`. `dst` accepts lengths up to `dstlen`.

#### base64Decode

```C
int base64Decode(const char *src, size_t srclen, uint8_t *dst, size_t dstlen);
```

Decodes the char string `src` of length `srclen` into the byte string `dst`. `dst` accepts length up to `dstlen`.